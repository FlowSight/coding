5. **Tool Implementation**: Each step is a Custom API (C#/.NET) registered in Dataverse. MCS calls them via HTTP.

### Key Design Decisions

* ## MCS Configuration & Prompt Engineering

Configuring MCS was a significant challenge. MCS has multiple configurable parts — **Knowledge**, **Instructions**, and **GPT parameters** (temperature, creativity, etc.). Getting the right combination required multiple rounds of trial and error to optimize for less hallucination, less context switching, and more accuracy.

**What we tried & learned**:

- Initial attempts mixed domain knowledge into instructions — led to LLM confusion, context switching between "what to do" and "what things are"
- Putting too much in instructions made the agent unpredictable on edge cases

**What worked — final configuration**:

| MCS Component                          | What we put there                                                                                                             | Why                                                                                                   |
| -------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------- |
| **Knowledge**                    | Domain context: what is a time entry, what tools are available, what each tool does, the step-by-step pipeline definition     | Gives the LLM stable reference material it can retrieve — doesn't compete with instruction following |
| **Instructions**                 | Minimal: "Execute the steps as per the knowledge with the input params"                                                       | Keeps the instruction slot clean and directive — LLM follows steps, doesn't improvise                |
| **Guardrails (in Instructions)** | Do NOT create entries outside the given date bounds. Do NOT generate assumed/fabricated comments — only use data from tools. | Prevents hallucination and out-of-scope actions                                                       |
| **GPT Parameters**               | Low temperature / creativity                                                                                                  | Deterministic task — we want consistency, not creativity                                             |

**Key insight**: Separating **"what things are"** (Knowledge) from **"what to do"** (Instructions) dramatically reduced hallucination. The LLM retrieves context from Knowledge and follows directives from Instructions — no mixing.

* ##  Context Window Optimization — Agent Metadata Table

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
