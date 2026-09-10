# **Problem 1: Cost — PAF invoked the premium MCS connector per user**

**Before (PAF premium Process license):** $1 \times \$150 = \$150/\text{month}$

**After (Durable Functions):** $4\text{ runs} \times \$0.12\text{-}\$0.31 = \$0.48\text{-}\$1.24/\text{month}$

**Savings:** $\$150 - \$0.48\text{-}\$1.24 = \$148.76\text{-}\$149.52/\text{month} = 99.2\%\text{-}99.7\%$

## Solution : Persistent Azure functions (Durable Functions)

Why not Power Automate Flow (PAF)?

1. **Cost at scale** — the premium MCS connector ran 10k times per weekly batch, consuming Power Automate premium/request capacity.
2. **Retry mismatch** — PAF provides fixed-interval retry, but MCS returns custom `Retry-After` headers requiring custom handling that PAF couldn't express
3. **Overkill guarantees** — PAF's approval workflows, conditional branching, UI — none needed for a batch dispatcher

Few facts on Azure Durable functions:

1. **Orchestrator**: coordinates work that must survive process recycling by replaying persisted orchestration history.
2. **Durable awaits**: orchestrators schedule and await Durable tasks such as activities and timers. Ordinary asynchronous I/O must not run directly in orchestrator code.
3. **Activity**: a stateless unit of work scheduled by an orchestrator to perform I/O or side effects; delivery is at-least-once, so it must be idempotent.
4. **Instance**: an orchestration instance is one persisted workflow run identified by an instance ID; a host instance is one VM/container replica that executes function invocations.

**What we replaced it with: Azure Durable Functions (orchestrator/activity + webhook split)**

The core happy path has four Azure Function definitions:

1. **`WeeklyTrigger` (starter)**: Timer-triggered at the start of the week and starts a new `DispatchOrchestrator` instance.
2. **`DispatchOrchestrator` (orchestrator/producer)**: Loads users, creates bounded batches, schedules one `DispatchUser` activity per user, and waits/checkpoints after each batch. It coordinates work but does not call MCS directly.
3. **`DispatchUser` (activity worker)**: Claims or resumes the user's `AgentState`, gets the S2S token from BAP RP, enqueues the request to MCS, and persists the lifecycle state and MCS correlation ID.
4. **`McsWebhook` (consumer)**: HTTP-triggered when MCS completes a conversation. It updates `AgentState` and notifies the user through Teams.

`ReconcileStale` is a fifth, recovery-focused timer function. `GetUsers` and `PersistFailedDispatches` are supporting activity functions referenced by the orchestrator.

**Why Durable Functions?**

- **Durable state is built in** — the Azure Storage provider creates task-hub resources automatically. Application state remains in Dataverse.

| What is stored | Table/resource name | SQL/NoSQL |
| --- | --- | --- |
| Orchestration events, checkpoints, and activity results | `<TaskHubName>History` | NoSQL key-value table |
| Instance status, input, and final output | `<TaskHubName>Instances` | NoSQL key-value table |
| Pending activity requests | `<TaskHubName>-workitems` | NoSQL message queue |
| Orchestrator events, activity responses, and timers | `<TaskHubName>-control-XX` | NoSQL message queue |
| Oversized payloads | `<TaskHubName>-largemessages` | NoSQL Blob object storage |
| Dispatch lifecycle, user/MCS correlation IDs, timestamps, result, and errors | `AgentState` | Relational Dataverse table |

`AgentState` has one row per user/week, keyed by deterministic `corrId`; `mcsCorrId` is nullable until MCS acknowledges the enqueue and has a unique index for reverse lookup and diagnostics.
- **Checkpoint and replay semantics** — not every C# `await` is a checkpoint. When an orchestrator schedules a Durable task and yields because it is incomplete, the runtime persists its history. After reactivation or restart, the orchestrator replays deterministically and resolves completed Durable calls from that history.
- **Failure recovery is at-least-once** — completed activity results in orchestration history are reused during replay, but an activity whose completion was not durably recorded may be delivered again. `DispatchUser` therefore must remain idempotent; recovery is not simply "resume at user #5001 with no re-processing."
- **Elastic worker scale-out** — the Azure Functions scale controller can add or remove host instances in response to queue pressure, subject to the hosting plan and platform limits. Worker count and pickup timing are not guaranteed by the orchestration code.
- **Concurrency control is per instance** — `maxConcurrentActivityFunctions` limits concurrent activity executions on each host instance, not across the entire scaled-out app. The 100-user application batch bounds one orchestration wave per org.
- **Durable infrastructure cost for 10k users** — assuming a 512 MB worker running for 1-3 seconds: $10{,}000 \times 0.5\text{ GB} \times 1\text{-}3\text{ s} \times \$0.000016/\text{GB-s} = \$0.08-\$0.24$. Including the webhook, orchestration, executions, and storage gives approximately **$0.12-$0.31 per run before free grants**.
- **Cost impact** — Durable Functions removed **10k PAF-to-MCS connector executions per run (~40k/month)**. Exact dollar savings require the tenant's Power Automate bill and capacity model. MCS cost was unchanged by this replacement because both designs still started one MCS conversation per user.

## **Problem: Unbounded fan-out delays dispatch and grows orchestration history**

Scheduling all 10k `DispatchUser` activities in one loop does not immediately make each activity available to workers. The orchestrator first schedules the entire fan-out in memory and yields at `Task.WhenAll`; only then does Durable Functions persist those scheduling decisions and make the activity messages available. This creates a large orchestration history and a burst of queued work.

**Solution: Bounded fan-out/fan-in batches**

- Schedule at most 100 users, then await that batch before scheduling the next one.
- Each `Task.WhenAll` is an explicit durable yield/checkpoint boundary, so workers can process the current batch before the next batch is created.
- At most 100 dispatch activities are outstanding from this orchestration at once. The Durable Functions runtime still determines actual dequeue timing, worker count, and concurrency within that limit.
- For 10k users and a batch size of 100, the orchestrator creates 100 application-defined waves. A slow user delays only the next wave, which is the throughput tradeoff for bounded queue pressure and history growth.

## **Problem: MCS accepts a request but its response is lost**

An enqueue timeout or dropped connection has an ambiguous outcome: MCS may have created a conversation even though the activity never received its MCS correlation ID. Blindly repeating a non-idempotent enqueue can create two conversations. Merely skipping when the `AgentState` claim already exists is also unsafe because it can leave a `claimed` row with no saved MCS correlation ID.

**Solution: Stable idempotency key and resumable dispatch state**

- Generate and persist the deterministic `corrId` before calling MCS, and send it as an idempotency key on every attempt.
- Require the MCS enqueue contract to deduplicate that key and return the original MCS correlation ID when the same request is replayed. A correlation ID used only for tracing is not sufficient.
- On a duplicate `AgentState` claim, return only for a terminal or already-dispatched state. Resume `claimed`, `dispatch_unknown`, and retryable states with the same idempotency key.
- On an ambiguous transport failure, set `dispatch_unknown` and let the Durable activity retry. Reconciliation first looks up that idempotency key in MCS; if absent, it schedules the same idempotent dispatch again.
- If MCS supports neither idempotent enqueue nor lookup by client request ID, exactly-once dispatch cannot be guaranteed across this network boundary. The system must choose between possible loss (do not retry) and possible duplication (retry).

**Monitoring (OOB)**:

- **Durable Functions Monitor** (VS Code extension) — visual dashboard of all orchestration instances, state timeline, per-step input/output
- **Application Insights** — distributed traces, failure alerts, latency percentiles. Query: "show failed orchestrations in last 24h"
- **Built-in HTTP status API** — `GET /runtime/webhooks/durableTask/instances/{id}` returns `Running | Completed | Failed` + full step history
- **Custom**: correlation IDs logged to App Insights and matched with `AgentState` for user-level traceability

```csharp
// 1. STARTER — Timer trigger, kicks off the orchestrator
[FunctionName("WeeklyTrigger")]
public async Task Run(
    [TimerTrigger("0 0 8 * * MON")] TimerInfo timer,
    [DurableClient] IDurableOrchestrationClient starter)
{
    await starter.StartNewAsync("DispatchOrchestrator", null);
}

// 2. ORCHESTRATOR — the "loop" that survives crashes
[FunctionName("DispatchOrchestrator")]
public async Task RunOrchestrator(
    [OrchestrationTrigger] IDurableOrchestrationContext ctx)
{
    var users = await ctx.CallActivityAsync<List<UserInfo>>("GetUsers", null);
    //         ^^^^^ checkpoint — result saved to Azure Storage

    // Bounded fan-out/fan-in: dispatch one wave before scheduling the next.
    const int dispatchBatchSize = 100;
    var retryOptions = new RetryOptions(TimeSpan.FromSeconds(5), maxNumberOfAttempts: 3);
    var results = new List<string>();

    for (var offset = 0; offset < users.Count; offset += dispatchBatchSize)
    {
        var batchTasks = users
            .Skip(offset)
            .Take(dispatchBatchSize)
            .Select(user => ctx.CallActivityWithRetryAsync<string>(
                "DispatchUser", retryOptions, user));

        // Await one wave and collect failures without stopping later batches.
        // On replay, completed activities resolve from history; unfinished
        // activities may be delivered again and rely on idempotency.
        var batchResults = await Task.WhenAll(batchTasks.Select(async task => {
            try { return await task; }
            catch (FunctionFailedException ex) { return $"FAILED:{ex.Message}"; }
        }));
        //                 ^^^^^ durable yield/checkpoint boundary per batch

        results.AddRange(batchResults);
    }

    // Persist failed dispatches for reconciliation
    var failed = results.Where(r => r.StartsWith("FAILED:")).ToList();
    if (failed.Any())
        await ctx.CallActivityAsync("PersistFailedDispatches", failed);
}

// 3. ACTIVITY — per-user work with idempotency guard
[FunctionName("DispatchUser")]
public async Task<string> DispatchUser(
    [ActivityTrigger] UserInfo user,
    ILogger log)
{
    var corrId = $"{user.Id}#{GetWeekStart():ddMMyy}";

    // IDEMPOTENCY: Claim one AgentState row (unique key on corrId).
    try
    {
        await _dataverse.CreateAsync("agentstate", new
        {
            corrid = corrId,
            userid = user.Id,
            state = "claimed",
            ts = DateTime.UtcNow
        });
    }
    catch (DuplicateKeyException)
    {
        var existing = await _dataverse.GetAsync<AgentState>("agentstate", corrId);

        if (existing.State == "dispatched" ||
            existing.State == "completed" ||
            existing.State == "failed")
        {
            log.LogInformation("Dispatch {CorrId} is already {State}", corrId, existing.State);
            return existing.McsCorrid ?? $"already_{existing.State}";
        }

        // A previous attempt stopped before its outcome was persisted. Resume
        // claimed/dispatch_unknown with the same MCS idempotency key.
        log.LogInformation("Resuming dispatch {CorrId} from state {State}", corrId, existing.State);
    }

    // Get S2S token for user impersonation
    var token = await _bapClient.GetS2STokenAsync(user.Id);

    // Enqueue to MCS — with custom retry respecting Retry-After header
    string mcsCorrid = null;
    const int maxRetries = 3;
    for (int attempt = 0; attempt < maxRetries; attempt++)
    {
        try
        {
            mcsCorrid = await _mcsClient.EnqueueAsync(
                new McsRequest
                {
                    UserId = user.Id,
                    StartDate = GetWeekStart(),
                    EndDate = GetWeekEnd(),
                    S2SToken = token,
                    CorrelationId = corrId
                },
                idempotencyKey: corrId);
            // MCS must return the original mcsCorrid when this key is replayed.
            break; // success
        }
        catch (McsThrottledException ex)
        {
            if (!ex.RetryAfter.HasValue || attempt == maxRetries - 1)
            {
                await _dataverse.UpdateAsync("agentstate", corrId, new
                {
                    state = "mcs_throttled",
                    lastError = ex.Message
                });
                throw;
            }

            // Respect MCS's requested delay — not arbitrary backoff
            log.LogWarning("MCS throttled (attempt {A}/{Max}), waiting {Delay}s",
                attempt + 1, maxRetries, ex.RetryAfter.Value.TotalSeconds);
            await Task.Delay(ex.RetryAfter.Value);
        }
        catch (McsAmbiguousTransportException ex)
        {
            // The request may already be accepted. Record uncertainty and let
            // Durable retry the activity with the same idempotency key.
            await _dataverse.UpdateAsync("agentstate", corrId, new
            {
                state = "dispatch_unknown",
                lastError = ex.Message
            });
            throw;
        }
    }

    if (mcsCorrid == null)
    {
        // Exhausted retries — mark as throttled, reconciliation will pick up
        await _dataverse.UpdateAsync("agentstate", corrId, new { state = "mcs_throttled" });
        throw new Exception($"MCS throttled after {maxRetries} attempts for user {user.Id}");
    }

    // Save the MCS correlation ID and lifecycle state in the same AgentState.
    await _dataverse.UpdateAsync("agentstate", corrId, new
    {
        mcscorrid = mcsCorrid,
        state = "dispatched"
    });

    log.LogInformation("Dispatched {UserId} with corrId {CorrId}", user.Id, corrId);
    return mcsCorrid;
}

// 4. CONSUMER — webhook called by MCS on conversation completion
[FunctionName("McsWebhook")]
public async Task<IActionResult> OnMcsComplete(
    [HttpTrigger(AuthorizationLevel.Function, "post")] HttpRequest req)
{
    var payload = await req.ReadFromJsonAsync<McsResult>();

    // Update the same AgentState created by DispatchUser.
    await _dataverse.UpdateAsync("agentstate", payload.CorrelationId, new
    {
        state = payload.Success ? "completed" : "failed",
        result = payload.Summary,
        completedAt = DateTime.UtcNow
    });

    // Notify user via Teams
    await _teamsClient.SendAsync(payload.UserId,
        $"Your time entries for this week have been created. {payload.Summary}");

    return new OkResult();
}

// 5. RECONCILIATION — picks up orphaned dispatches (no ack received)
[FunctionName("ReconcileStale")]
public async Task Reconcile(
    [TimerTrigger("0 0 */6 * * *")] TimerInfo timer)  // every 6 hours
{
    var staleThreshold = DateTime.UtcNow.AddHours(-4);
    var stale = await _dataverse.QueryAsync("agentstate",
        filter: $"(state eq 'claimed' or state eq 'dispatch_unknown' or state eq 'dispatched') and ts lt '{staleThreshold:O}'");

    foreach (var entry in stale)
    {
        if (entry.State != "dispatched")
        {
            var accepted = await _mcsClient.FindByIdempotencyKeyAsync(entry.CorrId);
            if (accepted != null)
            {
                await _dataverse.UpdateAsync("agentstate", entry.CorrId, new
                {
                    mcscorrid = accepted.CorrelationId,
                    state = "dispatched"
                });
            }
            else
            {
                // Re-enters DispatchUser; MCS deduplicates by the same corrId.
                await _dispatchRetryQueue.EnqueueAsync(entry.UserId);
            }
            continue;
        }

        // Check if TEs actually exist (source of truth)
        var tes = await _timeEntryService.GetExistingAsync(entry.UserId, entry.DateRange);
        var newState = tes.Any() ? "completed_reconciled" : "failed_stale";
        await _dataverse.UpdateAsync("agentstate", entry.CorrId, new { state = newState });
    }
}
```


# **Problem 2: Latency — sequential HTTP round-trips**

Each tool call was an HTTP request from MCS → Custom API → Dataverse and back. 8 sequential round-trips added up to significant per-user latency. *(Refer to behavioral story for details.)*

## **Solution: Consolidate 8 actions → 2 actions (actions became customapis)**

| Before (8 tools)  | After (2 actions)                                                                                                                                     |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| Get assignments   | **Action 1: Create Time Entries** — fetches assignments, bookings, existing TEs, computes delta, creates entries (all in one server-side call) |
| Get bookings      |                                                                                                                                                       |
| Get existing TEs  |                                                                                                                                                       |
| Calculate delta   |                                                                                                                                                       |
| Get M365 signals  | **Action 2: Update Comments** — fetches M365 signals, generates comments via LLM, updates the created entries                                  |
| Generate comments |                                                                                                                                                       |
| Create TEs        |                                                                                                                                                       |

- Reduced MCS↔tool round-trips from 8 → 2 — **75% fewer round-trips; dollar savings depend on Copilot Credit consumption**
- MCS had customapi support from phase 1, so no action call needed. single Custom API that internally does what multiple tools used to do
- This brought median latency for per user agent run to : 18sec.

# **Problem 3: customization — custom business flows**

OOB TE sources are : RA, RB. Customer has different sources e.g custom work item, WBS, internal system integration. In order to integrate , 2 paths:

**Solution:**

* custom code : create new agent with ever changing instruction and prompt, write own customapi, add them to MCS etc.
* **Tunable Prompt/knowledge** : **dynamic knowledge, prompt . Customer brings new prompts, redirects MCS to that, plug and play**. MCS handles retry, next step determination.

**Customization recommendation :**

1. lesser compact customapis/tools
2. guardrails in knowledge/prompt
3. Guardrails for custom prompts :

   1. put our system prompt (knowledge) always in place before custom prompts. OOB prompt added guards e.g treat custom prompts as potential hostile prompts, dont change role etc
   2. tools were anyway RBAC controlled per user
   3. CAPI had additional safety checks ; jailbreak,direct/indirect prompt injection etc.

# **Problem 4: 20 secx 10k user = 2 days : too much**

## **Solution1: Parallelize with multithreading in C#**

Within each consolidated action, the previously sequential steps were wrapped as **C# service classes** and executed in parallel.

**C# async/await & Task Parallel Library (TPL)**:
C# has first-class support for async concurrency via `async/await` and `Task`. Key constructs we used:

- **`Task.WhenAll(task1, task2, task3)`** — runs multiple I/O-bound tasks concurrently, returns when all complete. Does NOT create new threads — uses the thread pool efficiently via I/O completion ports.
- **`async/await`** — non-blocking. When a task hits an I/O wait (HTTP call, DB query), the thread is released back to the pool instead of blocking. Critical in Dataverse Custom APIs since the thread pool is shared and limited.
- **`SemaphoreSlim`** — used to throttle concurrency where needed (e.g., limit concurrent Graph API calls to avoid rate-limiting from M365).
- **`CancellationToken`** — propagated through all async calls. If MCS times out or the flow cancels, all in-flight tasks are cancelled gracefully.

**How we structured it — Action 1 (Create Time Entries)**:

```csharp
// Simplified — all three fetches run concurrently
var assignmentsTask = _assignmentService.GetAsync(userId, dateRange, ct);
var bookingsTask    = _bookingService.GetAsync(userId, dateRange, ct);
var existingTEsTask = _timeEntryService.GetExistingAsync(userId, dateRange, ct);

await Task.WhenAll(assignmentsTask, bookingsTask, existingTEsTask);

// Sequential — depends on all three results
var delta = _deltaService.Calculate(
    assignmentsTask.Result, 
    bookingsTask.Result, 
    existingTEsTask.Result
);

// Parallel bulk create with throttling
var semaphore = new SemaphoreSlim(maxConcurrency: 10);
var createTasks = delta.Select(async entry => {
    await semaphore.WaitAsync(ct);
    try { await _timeEntryService.CreateAsync(entry, ct); }
    finally { semaphore.Release(); }
});
await Task.WhenAll(createTasks);
```

**How we structured it — Action 2 (Update Comments)**:

```csharp
// Fetch M365 signals (meetings + emails) concurrently
var meetingsTask = _graphService.GetMeetingsAsync(userId, dateRange, ct);
var emailsTask   = _graphService.GetRelevantEmailsAsync(userId, dateRange, ct);

await Task.WhenAll(meetingsTask, emailsTask);

// Generate comments — sequential per TE (each needs LLM call, throttle to control cost)
foreach (var te in createdEntries) {
    var comment = await _commentService.GenerateAsync(te, meetingsTask.Result, emailsTask.Result, ct);
    await _timeEntryService.UpdateCommentAsync(te.Id, comment, ct);
}
```

**Key decisions**:

| Decision                                               | Why                                                                                                                                                |
| ------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| `async/await` over `Thread` / `Parallel.ForEach` | I/O-bound work (HTTP calls), not CPU-bound.`async` is non-blocking and doesn't waste threads waiting. `Parallel.ForEach` would block threads.  |
| `SemaphoreSlim` for throttling                       | Dataverse and M365 Graph have API rate limits. Unbounded `Task.WhenAll` over 1000 entries would trigger 429s. Semaphore caps in-flight requests. |
| `CancellationToken` propagation                      | Long-running per-user pipeline. If MCS or Power Automate times out, we need clean cancellation — not orphaned HTTP calls burning resources.       |
| Service class pattern                                  | Each tool (assignments, bookings, etc.) became a service class with a clean `async` interface. Easy to unit test, mock, and compose.             |

**Before vs After**:

| Metric                  | Sequential (before)         | Parallel (after)                             |
| ----------------------- | --------------------------- | -------------------------------------------- |
| Fetch phase (3 calls)   | ~3× latency of single call | ~1× (all concurrent)                        |
| Bulk create (N entries) | N × single create latency  | N/10 × single create latency (semaphore=10) |
| Thread usage            | 1 thread blocked per call   | Threads released during I/O waits            |

## solution 2 : Concurrency Control — OCC over Pessimistic Locking

With parallel writes (bulk create, comment updates), we needed a concurrency control strategy. We chose **Optimistic Concurrency Control (OCC)** over pessimistic locking for most entities.

**Why OCC**:

- The agent operates per-user in isolation — concurrent writes to the *same* row are rare (two agents won't create time entries for the same user simultaneously)
- Pessimistic locking (row-level locks) would serialize writes and negate the parallelization gains we just built
- OCC keeps writes non-blocking — no lock acquisition overhead, no deadlock risk

**How it works in Dataverse**:

- Each row has a `RowVersion` (ETag). On update, the client sends the ETag it last read.
- If another writer modified the row in between, the ETag won't match → Dataverse returns a **412 Precondition Failed**
- Client retries with fresh data (read-modify-write)

**When OCC conflicts actually happen**:

- User manually edits a time entry at the same moment the agent updates the comment → rare, but possible
- Two flows overlap for the same user due to retry/rerun → handled by idempotency checks (get existing TEs step)

**Why not pessimistic locking**:

- Dataverse pessimistic locks are table-scoped, not row-scoped in some scenarios — too coarse (sql server)
- Deadlock potential when multiple entities are updated in different order across parallel tasks

**Tradeoff**: OCC means occasional retry on conflict. But conflict rate is extremely low (<0.1% in production) given per-user isolation, so the throughput gain far outweighs the rare retry cost.
