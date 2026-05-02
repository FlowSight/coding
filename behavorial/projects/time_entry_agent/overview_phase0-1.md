# Time Entry Agent — Overview

## What
- GenAI-based RAG agent that uses various tools to create timesheets for enterprise users
- Based on work data — creates entries timely and efficiently
- Saves employees meta-work (no manual timesheet filling)

## Why
- Time entry is one of top 3 highest MAU modules in Dynamics 365 Project Operations
- D365: 20M MAU, Project Operations: 2M MAU, Time Entry: 1.2M MAU
- Manual timesheet creation is repetitive, error-prone, and hated by employees
- Part of Microsoft's Agent-first vision

## How
- RAG-based architecture with tool use
- Agent autonomously creates, submits timesheets without human interaction
- Unlike Copilot — no human instruction needed

## Key Metrics
- Scaled from 1k → 50k users per org
- Showcased at CEO Satya's 2025 Pinnacle Conference (CVP visibility)
- One of the key agents for Ignite conference

## My Role
- Led the design, team, owned e2e delivery
- Scaled from 0 to 200k users ground up
- Performance scaling in Phase 1

## Timeline
- TODO: fill in phases

## Diff vs Time Copilot
- Both help users create, submit, approve timesheets efficiently
- Copilot: needs human instruction and interaction
- Agent: autonomous, does not need human prompting


## Key Terms (for interviewer context)

- **CRM (Customer Relationship Management)**: Enterprise software for managing business data — customers, projects, resources, etc. Dynamics 365 is Microsoft's CRM platform.
- **Dataverse**: Microsoft's cloud data platform that backs Dynamics 365. Think of it as a managed relational database (tables, rows, columns) with built-in RBAC, API layer, and business logic triggers. All time entries, project assignments, bookings live here.
- **Custom API**: Server-side endpoints registered in Dataverse, written in C#/.NET. They execute business logic (validation, CRUD, calculations) and are callable via HTTP. The agent's tools are implemented as Custom APIs.
- **Power Automate Flow**: Microsoft's low-code workflow orchestration engine. Triggers can be scheduled (cron-like), event-driven, or manual. Flows chain steps — HTTP calls, conditionals, loops, connectors to other services.
- **MCS (Microsoft Copilot Studio)**: Microsoft's platform for building AI agents and copilots. Provides the RAG orchestration layer — you define topics (conversation flows), connect tools (plugins/actions), and MCS handles the LLM interaction, tool dispatch, and response generation. It receives a prompt + context, executes a predefined set of steps (each step = a tool call), and returns structured output. Essentially the "brain" of the agent.
- **Resource Assignment**: A project manager assigns an employee (resource) to a project task with expected hours. Stored in Dataverse.
- **Resource Booking**: A resource manager books an employee's capacity to a project for a date range. Represents "you're allocated to this project for X hours."
- **M365 (Microsoft 365)**: Outlook, Teams, Calendar — the agent pulls meeting and email data from here via Graph API to enrich time entries.

---

## Technical Details — High Level

### Architecture Flow

```
┌─────────────────┐     ┌──────────────┐     ┌─────────────┐
│  Power Automate │────▶│  Custom API   │────▶│  MCS (RAG)  │
│  (Scheduled)    │     │  (Dataverse)  │     │  Orchestrator│
└─────────────────┘     └──────────────┘     └──────┬──────┘
                                                     │
                         ┌───────────────────────────┤
                         ▼                           ▼
                   ┌───────────┐            ┌──────────────┐
                   │ Dataverse │            │  M365 Graph  │
                   │  Tables   │            │  API         │
                   └───────────┘            └──────────────┘
```

### Step-by-Step Execution

1. **Trigger**: Power Automate flow runs on a schedule (start of every weekday)
2. **User Iteration**: Flow fetches all eligible users from Dataverse, iterates per user
3. **Agent Invocation**: For each user, flow calls a Custom API which triggers MCS (RAG orchestrator) with:
   - User ID
   - Start and end date of the current week
4. **RAG Execution** — MCS runs a predefined pipeline of tool calls:

   | Step | Tool | What it does |
   |------|------|-------------|
   | a | Get Resource Assignments | Fetches project tasks the user is assigned to (from Dataverse) |
   | b | Get Resource Bookings | Fetches the user's booked capacity per project (from Dataverse) |
   | c | Get Existing Time Entries | Fetches any TEs already created for the date range (avoid duplicates) |
   | d | Calculate Delta | Computes intersection of (assignments + bookings) minus existing entries — determines what's missing |
   | e | Get M365 Signals | Pulls team meetings and relevant emails from Microsoft Graph API for the date range — enriches context |
   | f | Generate Comments | Makes a generative AI call (LLM) to create a human-readable comment/description per time entry |
   | g | Create Time Entries | Calls Dataverse Custom API to bulk-create the computed time entries |

5. **Tool Implementation**: Each step above is a Custom API (C#/.NET) registered in Dataverse. MCS calls them via HTTP.

### Key Design Decisions
- **Why RAG with tools vs. single LLM call?** — Deterministic steps (fetch data, compute delta) don't need LLM. Only the comment generation uses generative AI. Keeps cost low, latency predictable, and output reliable.
- **Why per-user iteration?** — Isolation: one user's failure doesn't block others. Also enables per-user RBAC — agent only accesses data the user has permission to see.

### User Impersonation (S2S On-Behalf-Of)

Per-user iteration was non-trivial. The agent runs as a **super user** (service principal with elevated rights), but all Dataverse queries and writes must happen **as the target user** — to respect row-level security, business unit scoping, and audit trails.

**Why needed**: Dataverse enforces RBAC at the row level. If the super user queried directly, it would either see all data (security violation) or need per-table security role hacks. Instead, we impersonate.

**Workflow**:
1. Super user iterates over users. Current user = User A.
2. Calls **BAP RP (Business Application Platform Resource Provider)** service to get an **S2S (server-to-server) on-behalf-of token** for User A.
3. All subsequent HTTP calls (Dataverse Custom APIs, Graph API) use this token — the platform treats these calls as if User A made them.
4. This ensures:
   - Data fetched is scoped to User A's permissions
   - Time entries created are owned by User A
   - Audit logs show User A as the actor (not the super user)

**Key terms**:
- **S2S token**: Server-to-server OAuth token — no user interaction needed, the service principal requests it programmatically.
- **BAP RP**: The Azure resource provider for Dynamics 365 / Power Platform. It issues impersonation tokens for registered service principals.
- **On-behalf-of**: OAuth flow where a service acts as a specific user. Different from app-only auth where the service acts as itself.

### MCS Configuration & Prompt Engineering

Configuring MCS was a significant challenge. MCS has multiple configurable parts — **Knowledge**, **Instructions**, and **GPT parameters** (temperature, creativity, etc.). Getting the right combination required multiple rounds of trial and error to optimize for less hallucination, less context switching, and more accuracy.

**What we tried & learned**:
- Initial attempts mixed domain knowledge into instructions — led to LLM confusion, context switching between "what to do" and "what things are"
- Putting too much in instructions made the agent unpredictable on edge cases

**What worked — final configuration**:

| MCS Component | What we put there | Why |
|---------------|-------------------|-----|
| **Knowledge** | Domain context: what is a time entry, what tools are available, what each tool does, the step-by-step pipeline definition | Gives the LLM stable reference material it can retrieve — doesn't compete with instruction following |
| **Instructions** | Minimal: "Execute the steps as per the knowledge with the input params" | Keeps the instruction slot clean and directive — LLM follows steps, doesn't improvise |
| **Guardrails (in Instructions)** | Do NOT create entries outside the given date bounds. Do NOT generate assumed/fabricated comments — only use data from tools. | Prevents hallucination and out-of-scope actions |
| **GPT Parameters** | Low temperature / creativity | Deterministic task — we want consistency, not creativity |

**Key insight**: Separating **"what things are"** (Knowledge) from **"what to do"** (Instructions) dramatically reduced hallucination. The LLM retrieves context from Knowledge and follows directives from Instructions — no mixing.

### Context Window Optimization — Agent Metadata Table

As the pipeline grew, tool outputs (resource assignments, bookings, existing entries) were bloating the LLM's context window. Each tool returned full JSON payloads, and by step d/e the accumulated context was approaching the model's token limit — causing truncation, degraded reasoning, and increased latency.

**Solution**: Created a new Dataverse table — **Agent Metadata** — as intermediate storage.

**How it works**:
```
Tool A executes → full JSON result saved to Agent Metadata table → returns only the GUID (primary key) to MCS
                                                                          │
MCS passes GUID to next tool → Tool B reads from Agent Metadata using GUID → processes → saves its result → returns GUID
                                                                          │
                                                                         ...and so on
```

**Before**: Tool output (potentially large JSON) → dumped into LLM context → context bloats with each step  
**After**: Tool output → stored in DB → only a GUID (36 chars) flows through the LLM context → next tool fetches full data from DB using GUID

**Why this matters**:
- **Context window stays lean** — LLM only sees GUIDs, not full data payloads. Frees up tokens for reasoning and instruction following.
- **No data loss** — full tool outputs are persisted in Dataverse, tools read them directly via GUID lookup.
- **Debuggability** — Agent Metadata table acts as a trace log. Can inspect intermediate results per user per run.
- **Decouples tool-to-tool data flow from LLM** — tools communicate via DB, LLM only orchestrates the sequencing.

### Action/Tool Optimizations — Cost & Latency

**Problem 1: Cost — $0.80 per MCS call × 8 tool calls per user**
Each MCS↔tool round-trip was a billable MCS call at ~$0.80. With 8 separate tool calls per user, cost per user per run was ~$6.40. At scale (50k users), this was unsustainable.

**Problem 2: Latency — sequential HTTP round-trips**
Each tool call was an HTTP request from MCS → Custom API → Dataverse and back. 8 sequential round-trips added up to significant per-user latency. *(Refer to behavioral story for details.)*

**Solution: Consolidate 8 tools → 2 actions**

| Before (8 tools) | After (2 actions) |
|---|---|
| Get assignments | **Action 1: Create Time Entries** — fetches assignments, bookings, existing TEs, computes delta, creates entries (all in one server-side call) |
| Get bookings | |
| Get existing TEs | |
| Calculate delta | |
| Get M365 signals | **Action 2: Update Comments** — fetches M365 signals, generates comments via LLM, updates the created entries |
| Generate comments | |
| Create TEs | |

- Reduced MCS↔tool round-trips from 8 → 2 — **~75% cost reduction**
- Each action is a single Custom API that internally does what multiple tools used to do

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

**Key decisions**:

| Decision | Why |
|----------|-----|
| `async/await` over `Thread` / `Parallel.ForEach` | I/O-bound work (HTTP calls), not CPU-bound. `async` is non-blocking and doesn't waste threads waiting. `Parallel.ForEach` would block threads. |
| `SemaphoreSlim` for throttling | Dataverse and M365 Graph have API rate limits. Unbounded `Task.WhenAll` over 1000 entries would trigger 429s. Semaphore caps in-flight requests. |
| `CancellationToken` propagation | Long-running per-user pipeline. If MCS or Power Automate times out, we need clean cancellation — not orphaned HTTP calls burning resources. |
| Service class pattern | Each tool (assignments, bookings, etc.) became a service class with a clean `async` interface. Easy to unit test, mock, and compose. |

**Before vs After**:

| Metric | Sequential (before) | Parallel (after) |
|--------|-------------------|------------------|
| Fetch phase (3 calls) | ~3× latency of single call | ~1× (all concurrent) |
| Bulk create (N entries) | N × single create latency | N/10 × single create latency (semaphore=10) |
| Thread usage | 1 thread blocked per call | Threads released during I/O waits |

### Concurrency Control — OCC over Pessimistic Locking

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

### Custom Correlation ID Framework

**Problem**: We originally relied on the `ConversationId` that MCS returned when we triggered a conversation. This ID was used across all tool calls and logged to power our monitoring dashboard (tracking per-user agent runs, latency, failures). A regression on MCS's side broke this — MCS stopped sending the correlation ID, which broke our dashboard and made debugging agent runs nearly impossible.

**Solution**: Built our own correlation ID framework instead of depending on MCS.

**How it works**:
- On every MCS invocation, we generate a unique correlation ID at our end **before** calling MCS
- The ID is a deterministic function of: `timestamp (truncated to ddmmyy, not sec/ms) + username + orgName`
  - Deterministic = if the same user in the same org triggers at the same DAY, it maps to the same ID (idempotency)
  - Unique in practice because timestamp granularity is sufficient
- This ID is passed as a parameter into MCS and propagated through every tool call in the pipeline
- Every Custom API (tool) receives and logs this ID → full traceability from trigger to final write

**Before**: MCS-provided `ConversationId` → broke when MCS regressed → no observability  
**After**: Self-generated correlation ID → decoupled from MCS internals → resilient

**Why this matters**:
- **No external dependency for observability** — we own the correlation, not MCS
- **End-to-end traceability** — single ID ties together: Power Automate trigger → MCS invocation → tool calls → Dataverse writes → Agent Metadata entries
- **Dashboard restored** — all monitoring and debugging queries key off this ID
- **Lesson learned**: Never depend on an external platform's internal IDs for your observability — always own your correlation.