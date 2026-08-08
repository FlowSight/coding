# **Problem 1: Cost — $0.80 per MCS call × 8 tool calls per user**

Each MCS↔tool round-trip was a billable MCS call at ~$0.80. With 8 separate tool calls per user, cost per user per run was ~$6.40. At scale (50k users), this was unsustainable.

## Solution : Persistent Azure functions (Durable Functions)

Why not Power Automate Flow (PAF)?

1. **Per-action cost inside the loop** — PAF bills per action execution (premium connector). 1 trigger, but 10k iterations × ~3 actions each (get token + call MCS connector + write state) = 30k billable actions/week. At ~$0.015/premium action = ~$450/week. MCS connector itself was an additional premium cost per invocation.
2. **Retry mismatch** — PAF provides fixed-interval retry, but MCS returns custom `Retry-After` headers requiring custom handling that PAF couldn't express
3. **Overkill guarantees** — PAF's approval workflows, conditional branching, UI — none needed for a batch dispatcher

Few facts on Azure Durable functions:

1. ORchestrator : **you have work that needs to survive process, in this case its the loop**
2. checkpoint at async : any async call is first dispatched to a worker, then checkpointed with the result.
3. It pushes async works into a queue (azure queue), where worker pull from them, if worker dies, another worker claims it,

**What we replaced it with: Azure Durable Functions (producer/consumer split)**

Two functions:

- **Function 1 (Producer)**: Timer-triggered on weekstart. Iterates users, gets S2S token from BAP RP per user, fire-and-forgets each user request into MCS, writes `{userid, corrid, mcscorrid, ts, state}` to ConvState table.
  - Needs persistance : MCS trigger is async call. Async call -> checkpoint -> wait
- **Function 2 (Consumer)**: HTTP-triggered webhook. MCS calls this on conversation completion. Updates ConvState/AgentState tables, notifies user via Teams connector.

**Why Durable Functions?**

- **Persistence is OOB** — uses Azure Storage (Tables + Queues + Blobs) automatically. No custom DB for orchestration state. Just point to a storage account in `host.json`.
- **Checkpointing** — each `await` is a checkpoint. If the VM dies mid-batch at user #5000, it resumes from user #5001 on restart. No re-processing.
- **Auto-scaling** — Consumption plan: 0→200 instances based on queue depth. Premium plan: pre-warmed instances, no cold start. For 10k users, it fans out across instances automatically.
- **Concurrency control** — `host.json` → `maxConcurrentActivityFunctions` caps parallel MCS calls to avoid rate-limiting.
- **Cost** — Consumption plan: pay per execution (~$0.000016/GB-s). 10k user dispatches ≈ pennies vs. $4k in PAF triggers.

**Monitoring (OOB)**:

- **Durable Functions Monitor** (VS Code extension) — visual dashboard of all orchestration instances, state timeline, per-step input/output
- **Application Insights** — distributed traces, failure alerts, latency percentiles. Query: "show failed orchestrations in last 24h"
- **Built-in HTTP status API** — `GET /runtime/webhooks/durableTask/instances/{id}` returns `Running | Completed | Failed` + full step history
- **Custom**: correlation IDs logged to App Insights, joined with ConvState table for user-level traceability

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

    // Fan-out: dispatch each user in parallel across worker instances
    var retryOptions = new RetryOptions(TimeSpan.FromSeconds(5), maxNumberOfAttempts: 3);
    var tasks = new List<Task<string>>();
    var failedUsers = new List<FailedDispatch>();

    foreach (var user in users)
    {
        tasks.Add(ctx.CallActivityWithRetryAsync<string>("DispatchUser", retryOptions, user));
    }

    // Await all — collect failures without stopping the batch
    var results = await Task.WhenAll(tasks.Select(async t => {
        try { return await t; }
        catch (FunctionFailedException ex) { return $"FAILED:{ex.Message}"; }
    }));
    //   ^^^^^ checkpoint — all results saved

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

    // IDEMPOTENCY: Try to claim slot in AgentState (unique key on corrId)
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
        // Already dispatched this user this week — skip, not an error
        log.LogInformation("User {UserId} already dispatched (corrId {CorrId}), skipping", user.Id, corrId);
        return "already_dispatched";
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
            mcsCorrid = await _mcsClient.EnqueueAsync(new McsRequest
            {
                UserId = user.Id,
                StartDate = GetWeekStart(),
                EndDate = GetWeekEnd(),
                S2SToken = token,
                CorrelationId = corrId
            });
            break; // success
        }
        catch (McsThrottledException ex) when (ex.RetryAfter.HasValue && attempt < maxRetries - 1)
        {
            // Respect MCS's requested delay — not arbitrary backoff
            log.LogWarning("MCS throttled (attempt {A}/{Max}), waiting {Delay}s",
                attempt + 1, maxRetries, ex.RetryAfter.Value.TotalSeconds);
            await Task.Delay(ex.RetryAfter.Value);
        }
    }

    if (mcsCorrid == null)
    {
        // Exhausted retries — mark as throttled, reconciliation will pick up
        await _dataverse.UpdateAsync("agentstate", corrId, new { state = "mcs_throttled" });
        throw new Exception($"MCS throttled after {maxRetries} attempts for user {user.Id}");
    }

    // Update AgentState with MCS correlation
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

    // Update AgentState
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
        filter: $"state eq 'dispatched' and ts lt '{staleThreshold:O}'");

    foreach (var entry in stale)
    {
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

- Reduced MCS↔tool round-trips from 8 → 2 — **~75% cost reduction**
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
