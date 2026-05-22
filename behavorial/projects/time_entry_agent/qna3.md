# Time Entry Agent — Senior-Level + Leadership Questions (Q7-Q12)

---

## Q7: What's the failure rate in production? What percentage of users get incorrect time entries?

### Answer Framework

"Let me break this into two categories — operational failures and quality failures:

**Operational failures (agent couldn't create entries):**
- Month 1 at scale: ~20% of users had at least one failed run per week. But we had less than <1k MAU combined.
- Top causes: [flaky MCS causing hallucination, manual agent stopping, token refresh failures]
- Current rate: ~3% after fixes 
- How we measure: Every run logs success/failure/partial to a kusto cluster ???. We have a dashboard that tracks daily success rate per org.


**Quality failures (agent created wrong entries):**
- we cant track if the TE hour was wrong or comment was wrong. only indicator is if user edits it.
- we do have failed

**How we measure quality at scale:**
- Automated: Compare agent-created entries vs. user-modified entries. If user edits, flag as potential quality issue.
- Manual: Sample 100 entries/week, human review for accuracy
- User feedback: [describe if there's a feedback mechanism]

**Key metrics:** 
    - how many Te failed to be created
    - for how many users it ran
    - which TE failed to gen comment
    - how many hours TE created by AI
    - how many number of TE created by AI 
    - how many ('87%) of entries are accepted without modification'" : query logic : which AI created TE are edited by human/ AI created TE

---

## Q8: If you had to rebuild this from scratch without any Microsoft platform constraints, what would you change?

### Answer

"Great question. Let me separate decisions I'd keep from ones I'd change:

**Decisions I'd KEEP (they're architecturally sound regardless of platform):**

1. **RAG with deterministic tools over pure LLM.** Only the comment generation needs an LLM. Fetching data, computing deltas, creating entries — these are deterministic. Using an LLM for them would add cost, latency, and unpredictability. This is a universal principle, not a Microsoft thing. 
    - but id probably replace MCS with microsoft agency or custom built RAG on Azure foundry or even just a non-LLM service with rule based tool calling.

2. **Per-user isolation.** Processing users independently gives fault isolation, respects per-user permissions, and enables horizontal scaling. I'd do this on any platform.

3. **Intermediate metadata storage for context window management.** The pattern of storing tool outputs externally and passing references through the LLM context — this is applicable to any LLM-based agent system. Context windows are always limited.

4. **OCC over pessimistic locking.** For a timesheet system with low write contention, optimistic concurrency is always the right choice.

**Decisions I'd CHANGE (forced by platform constraints):**

1. **Replace the scheduled workflow with a proper job queue.** We use Power Automate (a low-code workflow tool) as the scheduler because it's the platform's built-in option. If I had free choice, I'd use a message queue (SQS/Kafka) with worker pools. Benefits: better retry semantics, dead-letter queues, per-user backpressure, and no 30-second timeout constraint.

2. **Replace the AI orchestration platform with a lightweight agent framework.** We use Microsoft Copilot Studio because it's the company's prescribed agent platform. It adds latency (HTTP round-trips to/from the orchestrator) and cost (per-call billing). With free choice, I'd use something like LangChain or a custom orchestrator — direct function calls, no HTTP overhead, no per-call billing.

3. get rid of MCP

**The meta-lesson:** About 60% of the architecture is platform-agnostic good engineering. 40% was shaped by working within an enterprise platform's constraints. Knowing which is which is important — you don't want to cargo-cult platform-specific patterns into a greenfield system."

---

## Q9: You mentioned MCP in Phase 2 for tool standardization. But you already had working Custom APIs. What was the actual business justification for the migration? What did it cost?

### Answer

"Honest answer — the justification was a mix of strategic and tactical:

**Strategic (long-term):**
- Microsoft is moving all agent-tool communication to MCP (Model Context Protocol). In 12 months, Custom API registration in the orchestrator will be deprecated. If we don't migrate now, we'd have to do an emergency migration later under time pressure.
- MCP servers are **reusable across agents.** Our Dataverse MCP server is now used by 3 other agent teams. The M365 MCP server is used by 5. We built once, others benefit. Before MCP, every team wrote their own HTTP integrations.
- real reasoon : business and leadership pressure

**Tactical (immediate benefit):**
- **Tool discovery.** MCP provides a standardized way for the orchestrator to discover available tools at runtime. Before, tools were hardcoded in the orchestrator config. Adding a new tool required a config deployment. Now, the MCP server registers tools dynamically.
- **Reduced hallucination.** This was the unexpected win. When we first connected to MCP, the orchestrator saw ALL tools globally (dozens from other teams). The LLM started picking random irrelevant tools. We solved this with Service Tree ID scoping — the orchestrator only sees tools registered under our service identity. This actually improved accuracy vs. Phase 1.

**What it cost:**
- ~3 engineer-weeks of my team's time
- Co-development with the MCP server team for 2 weeks (they needed to add entity set support for our use cases)
- Zero downtime — we ran MCP and direct Custom APIs in parallel with a feature flag, validated MCP results matched, then cut over
- Added a fallback path: if MCP fails, we fall back to direct Custom APIs (Phase 1 endpoints still exist)

**Would I do it again?** Yes, but I'd push back on the timeline. We migrated 2 months earlier than necessary, which created pressure. In hindsight, I'd wait until the MCP server was more mature — we spent time debugging their gaps that they would have fixed anyway."

---

## Q10: How did you handle the LLM generating wrong comments? What's your feedback loop?

### Answer

"LLM comment generation was the highest-risk part of the system. Here's how we managed it:

**Prevention (before generation):**
- Low temperature / low creativity in model params — we want consistency, not creativity
- Prompt engineering: 'Generate a factual description of work done based ONLY on the following data. Do NOT infer or assume activities not present in the data.'
- Guardrails in system prompt: 'Do NOT reference dates outside the given range. Do NOT fabricate meeting names or project names.'
- Input validation: Only pass verified data (assignments, bookings, calendar events) — no user-generated free text that could inject prompt manipulation
- RAI check already done in cAPI

**Detection (after generation):**
- **Automated checks:** 
  - RAI check
  - length check
  - project, task, resource , subcon name content check in comment
- **User behavior signal:** If a user edits or deletes an agent-generated comment within 24 hours, we log it as a potential quality issue. If edit rate for a specific comment pattern exceeds threshold, we investigate.

**Correction:**
- Users can edit comments directly — it's just a text field on the time entry
- We do have a direct 'thumbs up/thumbs down' feedback mechanism yet
- A/B test with control and placebo prompts in phase 1.

**What we found:**
- [20% of comments were edited by users in phase 0]
- [ Main issues were — e.g., generic comments, unexcted words etc.]
- control group corrected <10%
- [ After prompt tuning, MCS maturity, edit rate dropped to 12% in phase 1 ]

**What I'd improve:**
- Add explicit user feedback (thumbs up/down on generated comments)
- Use feedback data to fine-tune the prompt or switch to a fine-tuned model
- A/B test different comment styles (brief vs. detailed) to see what users prefer"

### GAP: You need real quality metrics here. The framework is solid but the interviewer will push for numbers.

---

## Q11: How did you influence the team? What was the hardest technical disagreement you had on this project?

### Answer Framework

Pick ONE specific disagreement. Structure it as:

**"The hardest disagreement was about [TOPIC].**

**Context:** [Who disagreed, what were the two positions]

**Position A (theirs):** [What they wanted and why it made sense to them]

**Position B (mine):** [What I wanted and why]

**How I handled it:**
- I didn't pull rank or escalate immediately
- I [built a prototype / ran a load test / wrote a design doc with data]
- Presented the evidence to the team
- [The other person was convinced / we found a middle ground / I was wrong about part of it]

**Outcome:** [What we shipped, what the result was]

**What I learned:** [Something about collaboration, not just 'I was right']"

### Example topics from your project (pick the real one):
- 8 tools vs 2 actions — did someone argue against consolidation?
- Sync vs async processing — did someone want to keep synchronous?
- MCP migration timing — did you push back on the platform team's timeline?
- Using Dataverse for metadata vs. an external store — was there debate?
- Per-user iteration vs batch processing — did someone want the batch approach?

---

## Q12: What's your proudest engineering decision on this project, and what's the one you regret most?

### Answer Framework

**Proudest:**

Pick something non-obvious — not "we made it fast." Pick an architectural decision that showed foresight.

Candidates from your project:
- **Separating Knowledge from Instructions in the LLM config** — this reduced hallucination dramatically and became a pattern other teams adopted
- **Agent Metadata table for context window management** — elegant solution that also gave free debuggability
- **Making the concurrency limit configurable** — showed foresight for multi-customer deployment

Structure: "I'm proudest of [decision] because [short-term benefit] AND [long-term benefit that wasn't obvious at the time]."

**Regret:**

This MUST be genuine. Interviewers detect rehearsed fake regrets instantly.

Candidates from your project:
- **Not load-testing at 10x target from day 1** — each scale milestone broke something we could have caught earlier
- **Migrating to MCP too early** — spent engineering time debugging their platform gaps
- **Not building a user feedback loop for LLM comments** — we still don't have direct quality signal from users
- **Not abstracting the tool interface from the start** — the Phase 1 → Phase 2 migration wouldn't have been needed if we'd designed for pluggable tool backends initially

Structure: "I regret [decision] because [what it cost us]. If I could redo it, I'd [specific change]. The lesson is [principle]."

---

## Final Prep Checklist

Before the interview, make sure you can answer from memory:
- [ ] 90-second pitch without jargon (Q0)
- [ ] One specific scaling failure story with timeline (Q1)
- [ ] The SemaphoreSlim math — don't fumble this (Q4)
- [ ] Real production quality numbers (Q7, Q10) — **FILL THESE IN**
- [ ] One genuine technical disagreement with resolution (Q11)
- [ ] One real regret with what you learned (Q12)
- [ ] Platform-agnostic vs platform-constrained decisions list (Q8)
