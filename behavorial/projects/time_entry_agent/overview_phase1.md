## * Action/Tool Optimizations — Cost & Latency

**Problem 1: Cost — $0.80 per MCS call × 8 tool calls per user**
Each MCS↔tool round-trip was a billable MCS call at ~$0.80. With 8 separate tool calls per user, cost per user per run was ~$6.40. At scale (50k users), this was unsustainable.

**Problem 2: Latency — sequential HTTP round-trips**
Each tool call was an HTTP request from MCS → Custom API → Dataverse and back. 8 sequential round-trips added up to significant per-user latency. *(Refer to behavioral story for details.)*

**Solution: Consolidate 8 tools → 2 actions**

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

**Problem 3: customization — custom business flows**
OOB TE sources are : RA, RB. Customer has different sources e.g custom work item, WBS, internal system integration. In order to integrate , 2 paths:

**Solution:**

* custom code : create new agent with ever changing instruction and prompt, write own customapi, add them to MCS etc.
* **Tunable Prompt/knowledge** : **dynamic knowledge, prompt . Customer brings new prompts, redirects MCS to that, plug and play**. MCS handles retry, next step determination.

**Solution: Parallelize with multithreading in C#**

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

##### **Customization recommendation :**

1. lesser compact customapis/tools
2. guardrails in knowledge/prompt
3. Our fallback :

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

## * Concurrency Control — OCC over Pessimistic Locking

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

- Dataverse pessimistic locks are table-scoped, not row-scoped in some scenarios — too coarse
- Locks held during HTTP round-trips (LLM comment generation) would block other operations for seconds
- Deadlock potential when multiple entities are updated in different order across parallel tasks

**Tradeoff**: OCC means occasional retry on conflict. But conflict rate is extremely low (<0.1% in production) given per-user isolation, so the throughput gain far outweighs the rare retry cost.

### MCS Configuration & Prompt Engineering

MCS has multiple configurable parts — **Knowledge**, **Instructions**, and **GPT parameters** (temperature, creativity, etc.). Getting the right combination required multiple rounds of trial and error to optimize for less hallucination, less context switching, and more accuracy. PLUS  WE HAD TO SUPPORT CUSTOMIZATION STORY.

**What we tried & learned**:

- Initial attempts mixed domain knowledge into instructions — led to LLM confusion, context switching between "what to do" and "what things are"
- Putting too much in instructions made the agent unpredictable on edge cases

**What worked — final configuration**:

| MCS Component                          | What we put there                                                                                                                                                                    | Why                                                                                                   |
| -------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------- |
| **Knowledge**                    | Acts like a system prompt, LEVERAGED BY**KV CACHE**. Domain context: what is a time entry, what tools are available, what each tool does, the step-by-step pipeline definition | Gives the LLM stable reference material it can retrieve — doesn't compete with instruction following |
| **Instructions**                 | Minimal: "Execute the steps as per the knowledge with the input params"                                                                                                              | Keeps the instruction slot clean and directive — LLM follows steps, doesn't improvise                |
| **Guardrails (in Instructions)** | Do NOT create entries outside the given date bounds. Do NOT generate assumed/fabricated comments — only use data from tools.                                                        | Prevents hallucination and out-of-scope actions                                                       |
| **GPT Parameters**               | temperature  == 0/ creativity                                                                                                                                                        | Deterministic task — we want consistency, not creativity                                             |

**Key insight**: Separating **"what things are"** (Knowledge) from **"what to do"** (Instructions), temp == 0, less tools exposure, dramatically reduced hallucination. The LLM retrieves context from Knowledge and follows directives from Instructions — no mixing.
