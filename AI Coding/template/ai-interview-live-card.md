# 45-Minute AI Interview Live Card

Use this card during practice. In the real interview, create only the short task note
and use the prompts that the controlled environment permits.

## North Star

**Requirement -> invariant -> smallest change -> predicted check -> evidence.**

AI, hints, and visible tests are inputs. I own the decision and the code.

[AI coding basics](../basics.md) and [AI coding mistakes](../mistakes.md) are the
controlling interaction guidance for this card.

## Human-First Loop

For every AI turn:
<span class="action-chip action-do">THINK</span> ->
<span class="action-chip action-say">SAY INTENT</span> ->
<span class="action-chip action-prompt">PROMPT</span> ->
<span class="action-chip action-verify">REVIEW ALOUD</span> ->
<span class="action-chip action-verify">VERIFY</span>.
Form your own approach first, delegate one bounded task, read every generated change,
flag anything off, and run the available code/tests before another edit or phase.

## Clock

| Time | Action | Hard gate |
|---|---|---|
| 0-0:30 | Ask how checkpoints arrive; inspect pre-existing Git changes | Starting conditions clear |
| 0:30-7 | Agent research: write only three research artifacts | Orientation gate passes |
| 7-9 | Complete task note; state human direction; Plan; persist all slices | Complete plan persisted; first slice selected |
| 9-34 | Agent implementation: execute approved plan | All required tasks complete by 34 |
| 34-40 | Agent integration: broad checks and required fixes | Integrated result green |
| 40-43 | Review changed regions; explain complexity and tradeoff | Own every retained line |
| 43-45 | Summarize completed work, evidence, AI judgment, and risk | Clear close |

### Implementation budgets

- 2 tasks: `13 / 12`
- 3 tasks: `9 / 8 / 8`
- 4 tasks: `7 / 6 / 6 / 6`
- 5 tasks: `5 / 5 / 5 / 5 / 5`

Each number includes review and a focused check.

## <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Opening

> I will first research the entire first-party repository in three short passes and
> save each pass under `.interview/research/`. For each checkpoint I will maintain one
> `task_<id>.md` with current context, accepted plan, and latest result. Before each
> prompt I will state my intent; afterward I will review the output aloud and test
> every code or test change before continuing.

> [!NOTE]
> <strong class="action-chip action-know">KNOW</strong>
> Git, model switching, and AI search/read/edit/run/tool capabilities are guaranteed.
> Do not spend time asking about them.

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> "Will you show me all checkpoints now, or reveal them one at a time?"

### <span class="action-chip action-do">DO YOURSELF</span> Inspect Starter Changes

1. Run `git status --short`.

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Only if Git shows pre-existing changes</summary>

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> "These files were already modified before I started. Should I preserve those
> changes as part of the starter code?"

</details>

## Full-Codebase Orientation

> [!NOTE]
> <strong class="action-chip action-know">KNOW</strong>
> Mode sequence: `Agent research -> Agent task prep -> human direction -> Plan -> persist complete plan -> Agent implementation -> Agent integration`.

- **Agent research:** Prompts 1-3; edit only `.interview/research/*.md`.
- **Agent task prep:** for a clear task, AI fills only the task note. Use discovery
   and parent-managed subagents only when the task or acceptance is unclear.
- **Human direction:** state your simplest approach/order and predicted check before
   asking AI to plan.
- **Plan:** Prompt 4 reads the current task file; edit nothing.
- **Plan persistence:** manually copy the complete accepted plan or use a dedicated
   Agent persist-only turn; verify every slice before implementation.
- **Agent implementation:** name one persisted slice ID, implement only that slice,
   test after every change, then replace Latest Snapshot.

### <span class="action-chip action-do">DO YOURSELF</span> Choose One Input Method

- **Copy/paste allowed:** use the
   [full prompt index](codebase-orientation/README.md) and send each prompt unchanged.
- **Copy/paste prohibited:** open the same numbered file and type its self-contained
   Quick Prompt. No separate setup prompt is needed.

Never customize a fixed prompt; your short task-note values and `CURRENT_TASK` path
are the only dynamic inputs. For every row: submit one prompt, wait for its output
file, open and understand it, then continue. Do not discuss the checkpoint in passes
1-3.

| Time | <span class="action-chip action-prompt">PROMPT TO AI</span> | <span class="action-chip action-output">AI OUTPUT</span> Persisted artifact |
|---|---|---|
| 0:30-4:15 | Architecture, HLD/LLD, flows, tests/coverage, class/method comment audit | `.interview/research/00-architecture-tests-and-comments.md`; no project-file edits |
| 4:15-5:30 | Bugs, unfinished work, gaps, and risks only | `.interview/research/01-bugs-gaps-and-risks.md` |
| 5:30-7:00 | Verify links/diagrams/claims and synthesize | `.interview/research/02-orientation-summary.md` |

*<span class="action-chip action-wait">WAIT</span> After each row, let AI finish and
open the artifact before sending the next prompt.*

Full orientation covers every first-party top-level module, high-level architecture,
important low-level classes/functions/data structures, primary success/error/data
flows, every component in those flows, bugs, gaps, tests, and incomplete tests.
Exclude dependencies, generated files, vendored code, and build output.

### <span class="action-chip action-verify">VERIFY</span> Orientation Gate

- [ ] All three research files exist under `.interview/research/`.
- [ ] Pass 1 is <=180 lines; Passes 2/3 are <=100; Plan fits its type cap:
   bug `60`, feature `90`, optimization `80`, refactor `75`.
- [ ] Each artifact starts with its briefing and uses compact tables.
- [ ] `git diff` shows only research Markdown changes.
- [ ] Existing comments on every critical or large class and method are
   classified ADEQUATE, NEEDS_ENHANCEMENT, or
   MISSING, with proposed comments recorded only in Pass 1's artifact.
- [ ] Representative evidence links support the reviewed claims.
- [ ] No unresolved broken links or contradictions remain.

> [!NOTE]
> <strong class="action-chip action-know">KNOW BEFORE CONTINUING</strong>
> Be able to explain each module's job, primary flows, important symbols/data changes,
> validation methods, coverage gaps, finding types, and required diagrams.

Research is incomplete while it exists only in chat. Do not proceed unless the gate
passes or the remaining `UNKNOWN` items are explicitly non-blocking.

## Focus on the Current Checkpoint

### Establish context

### <span class="action-chip action-do">DO YOURSELF</span> Default: Task Is Clear

1. Create `.interview/tasks/task_T1.md` from the table-free
   [task template](checkpoint-task-files/README.md), manually or with Prompt 4's
   short AI seed.
2. Fill `Task` and anything obvious; mark the rest `TO BE FILLED BY AGENT`. Budget
   under 30 seconds.
3. In Agent mode, send:

```text
COMPLETE CURRENT TASK
```

| AI OUTPUT |
|---|
| Agent fills the note from evidence, preserves the explicit task, and sets `CONTEXT_READY`. |

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Only when task or acceptance is unclear</summary>

### <span class="action-chip action-prompt">PROMPT TO AI</span> Discover Unclear Task

```text
DISCOVER UNCLEAR TASK
```

| AI OUTPUT |
|---|
| Parent Agent may use two read-only workers, then writes one grounded Behavior Trace. |

### <span class="action-chip action-verify">VERIFY</span> Unclear-Task Evidence

- [ ] Trace reads `signal -> expected source -> entry -> relevant path -> exact gap`.
- [ ] If still `AMBIGUOUS`, confirm task/scope with the interviewer.

</details>

### Plan the context

### <span class="action-chip action-do">DO YOURSELF</span> Form Your Direction First

Before Plan mode, spend 30-60 seconds stating the acceptance condition, simplest
likely approach/flow order, and predicted first check. Prefer existing helpers and a
direct solution; do not delegate the architecture decision.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Plan Intent

> "My current approach is `<approach/order>`, and `<check>` should prove the first
> part. I will compare AI's bounded plan against this direction."

### <span class="action-chip action-prompt">PROMPT TO AI</span> Plan Mode

1. Send `CURRENT_TASK: .interview/tasks/task_T1.md`, then switch to Plan mode.
2. Choose one Prompt 4 variant:
   `BUGFIX / FEATURE / OPTIMIZATION / ENHANCEMENT-REFACTOR`.
3. Run its full prompt unchanged or matching Quick Prompt. If context is missing or
   ambiguous, AI asks up to three concise questions in chat, one at a time. Answer;
   Plan mode uses the answer without editing. Agent mode persists it with the accepted
   plan in the separate persistence step before coding.
### <span class="action-chip action-verify">VERIFY</span> Plan Context

- [ ] Acceptance, cause/gap, invariants, contracts, slices, and validation are grounded.
- [ ] Plan fits its cap: bug `60`, feature `90`, optimization `80`, refactor `75` lines.
- [ ] The final line of the entire Plan response is `Plan self-check: PASS`.

### Resolve questions before accepting

Use the task, tests, APIs/schemas, and research to remove answerable unknowns. Ask at
most three questions only when an answer changes code or acceptance; state a cheap,
reversible assumption instead of asking.

### Check invariants during Plan review

An invariant matters here, before execution: it is behavior the slice must not break.
Take the task-relevant invariant and preserving check from the Plan response. Do not
pause an already-running implementation turn to rediscover it.

Say: "`<invariant>` remains true; `<test/contract>` proves it; slice `<ID>` preserves
it through `<change>`."

#### Required

Acceptance, 1-3 evidenced invariants, all numbered slices with `Change` and `Check`,
all-tests-after-every-change rule, final broad check, and complexity/risk.

#### <span class="action-chip action-optional">OPTIONAL</span> When Relevant

Multiple slices, dependencies, rollback, alternatives, migration/compatibility,
benchmark threshold, security/concurrency, and external failures.

### Review the Plan Before Accepting

You are verifying the AI's complete Plan-mode response before approving it. Plan mode
returns **all slices at once**, in execution order; it does not return one per turn.

> [!NOTE]
> <strong class="action-chip action-know">KNOW</strong>
> A slice is one numbered implementation part. A small task uses one. For a large
> scope, split by working behavior such as `Flow 1`, then `Flow 2`, not code layers.

> [!IMPORTANT]
> **EACH SLICE IS SHORT**
> - `### <ID>: <flow or implementation part>`
> - `Change: <bounded behavior and likely files/symbols>`
> - `Check: <observable test or result>`
>
> After every slice and final validation, the final line of the **entire Plan
> response** is `Plan self-check: PASS`.
>
> Prompt 4 makes AI self-check and rewrite before responding. This is not an absolute
> model guarantee; reject or rewrite any plan that breaks the contract.

### <span class="action-chip action-verify">VERIFY</span> Before Accepting

- [ ] All implementation parts are present in one response and ordered sensibly.
- [ ] Every slice has a bounded `Change` and a proving `Check`.
- [ ] Every acceptance criterion maps to a slice/check.
- [ ] Plan requires all available tests after every code or test change.
- [ ] Every deviation from your stated direction has requirement/code/test evidence.
- [ ] No unnecessary rewrite, hierarchy, nested class design, or abstraction remains.
- [ ] Vague or oversized slices were rewritten by AI.
- [ ] The entire response ends with `Plan self-check: PASS`.

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> State the accepted slice order and why.

### Persist every slice before implementation

Choose **one** method. Do not do both.

### <span class="action-chip action-prompt">PROMPT TO AI</span> Default: AI Copy

Use when Agent mode can read the Plan response and write the task file:

```text
PERSIST ACCEPTED PLAN ONLY.
Read CURRENT_TASK and the final accepted Plan response in this conversation.
Replace Accepted Plan with that complete response: acceptance, invariants, every
slice in order with Change and Check, the all-tests-after-every-change rule, final
broad validation, complexity/risk, and the final Plan self-check: PASS line.
Do not edit source, tests, configuration, or build files. Do not implement any slice.
Re-read the task file, report the persisted slice IDs in order, and stop.
```

### <span class="action-chip action-do">DO YOURSELF</span> Alternative: Manual Copy

Use when manual copy is available and faster, or Agent mode cannot reliably see the
Plan response. Copy the complete final response into **Accepted Plan**, replacing the
old plan. Do not run AI Copy afterward.

### <span class="action-chip action-verify">VERIFY</span> Persistence Gate

- [ ] The final plan, not a summary, is under **Accepted Plan**.
- [ ] Every slice ID appears exactly once and in order with `Change` and `Check`.
- [ ] Plan-wide test and final-validation rules are present.
- [ ] No source, test, configuration, or build file changed.

Do not implement until all checks pass. Repeat this gate after any replan.

### <span class="action-chip action-verify">VERIFY</span> Ready to Implement

- [ ] Complete Plan is persisted and no source/test file changed during persistence.
- [ ] The slices' `Change`, `Check`, and key preserving invariants are understood.

## Execute One Slice: Who Does What

The AI Copy step may have used a persist-only Agent turn; that turn stopped without
coding. The following is the first implementation turn.

### <span class="action-chip action-do">DO YOURSELF</span> Select One Slice

1. Verify the complete accepted plan is persisted.
2. Choose one persisted slice ID.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Execution Intent

> "I am asking AI to implement only `<ID>` because `<reason>`. I expect `<check>`,
> then I will review every changed line and test result before continuing."

### <span class="action-chip action-prompt">PROMPT TO AI</span> Execute One Slice

```text
Execute only slice <ID> from CURRENT_TASK.
The complete accepted plan is already persisted; do not replace or summarize it.
Do not start another slice.
After every code or test change, run all available test cases before another change.
Update Latest Snapshot. Report completed or blocked, then stop.
```

### <span class="action-chip action-know">KNOW</span> Agent Responsibilities

1. Stops without project edits if the complete plan or named slice is missing.
2. Leaves Accepted Plan unchanged and edits only the named slice.
3. After every code/test change, runs every exposed test before another edit.
4. Reviews changed code, replaces Latest Snapshot, reports completed/blocked, stops.

### <span class="action-chip action-output">AI OUTPUT</span> Latest Snapshot

The same implementation turn updates this immediately before stopping. It is not a
second prompt. It records status, changed files/behavior, tests, remaining work, and
risk/complexity.

### <span class="action-chip action-verify">VERIFY</span> After Agent Stops

1. Read every changed line and inspect the actual test output.
2. Review aloud what matched, what looks wrong or surprising, and what you accept,
   revise, or reject.
3. Confirm Latest Snapshot matches the actual files and results.
4. Do not send another prompt or start another slice until retained code is understood
   and all exposed test results are green or explicitly explained.
5. If blocked, debug the same slice. If the plan is wrong, state why before replanning.
6. If completed, either start a new Agent turn naming the next slice or close the task.

No separate ledger and no manual slice-status bookkeeping are needed; the Agent-owned
Latest Snapshot is the progress record.

### Parallelism

- Use only for the rare unclear-task path or unusually valuable read-only review.
- Send one prompt to the main Agent; do not launch helpers yourself.
- That prompt tells the parent to internally spawn at most two read-only workers for
   independent signal/contract and code-path evidence, then reconcile their output.
- If spawning is unavailable, the parent performs both passes sequentially.
- The parent is the only writer. Never parallelize edits or dependent slices.

Handoff:

> Slice __ is completed. Its focused check proves __, and the full exposed suite passes.
> Complexity is __. I am stopping before slice __.

## Type-Specific Completion Checks

Agent checks the relevant line while implementing. Candidate verifies its
evidence before saying the task is complete; this is not a separate loop.

### Bug fix

`one slice normally: observe -> hypothesis -> regression -> minimal repair -> all tests`

### Feature

`contract -> one slice if small; otherwise optional vertical slices -> all tests`

### Performance

`semantics -> baseline -> one experiment; add experiments only if needed -> all tests`

### Enhancement

`characterize -> one boundary slice; add slices only if needed -> all tests`

## After the Task Is Done

**Agent mode, before stopping the final slice:**

1. Runs the full exposed test suite and any separate build/typecheck again.
2. Confirms every acceptance criterion and invariant has evidence.
3. Replaces Latest Snapshot with `COMPLETED`, files, test results, complexity,
   limitations, and residual risk.

**Candidate after Agent stops:**

1. Review the final diff and test output.
2. If anything is failing or unexplained, continue the same task.
3. Give this spoken summary: "Task `<ID>` is complete; `<acceptance>` works; I changed
   `<files/behavior>`; `<full-suite result>` passed; complexity/risk is `<...>`."
4. Create the next task file for another checkpoint, or start integration if finished.

## Fixed AI Prompts

Send unchanged; they use the current research, accepted plan, code, and output.

For implementation:

```text
Read CURRENT_TASK and the accepted Plan response. If the complete accepted plan is
absent, stale, incomplete, or missing the named slice, do not edit project files;
report that persistence must be completed first, then stop. Do not replace or
summarize Accepted Plan. Implement only the slice ID named by the candidate; do not
start another slice. After every code or test
change, run all available test cases before making another change. Use the full Run
Tests/Build control when applicable; record hidden/unavailable limits. Preserve
contracts/prior behavior. Replace Latest Snapshot with status, change summary, files,
validation/result, remaining work, and risk/complexity. Report completed or blocked;
stop.
```

For debugging:

> Use the current failure, changed code, and accepted plan. Do not edit. Return
> at most three ranked causes with evidence and the cheapest distinguishing check.

For review:

> Review current changes against the accepted plan and repository contracts. Rank
> correctness, edge, API, type, error, concurrency, regression, and complexity risks.
> Do not edit or suggest style-only work.

## <span class="action-chip action-know">KNOW</span> AI Spiral Stop Rules

Switch to manual work for this checkpoint after:

- two misses;
- uncertainty followed by an unsolicited rewrite, restructuring, or start-over plan;
- repeated requirement or API drift;
- deleted or weakened tests;
- hardcoding, swallowed errors, or unsafe typing; or
- output too large to review within the budget.

Do not build on unreviewed output. Do not switch models unless explicitly justified
and allowed.

### <span class="action-chip action-know">KNOW</span> Nerfed AI Fallback

If AI gives only hints, cryptic/incomplete responses, or refusals, use it only for
boilerplate, unfamiliar syntax, or basic scaffolding you can fully review. Do the
algorithm, architecture, debugging hypothesis, and hard coding yourself instead of
re-prompting for a solution.

## Pushback Protocol

> Let me test that suggestion against requirement __. With input __, it produces __,
> which violates invariant __. I recommend __. If the intended requirement changed,
> I will record the delta and adapt.

Accept evidence quickly. Reject authority calmly. Never argue for ego.

## Hidden-Test Sweep

- [ ] empty/null/missing input
- [ ] min/max/overflow/off-by-one
- [ ] duplicates/ties/order/determinism
- [ ] mutation/aliasing/repeated calls
- [ ] invalid input/partial failure
- [ ] concurrency/cancellation/cleanup
- [ ] environment/time/filesystem/network assumptions

## Minute Alarms

- **19:** First checkpoint should be green.
- **26:** At least half should be green; reorder independent work if needed.
- **30:** Drop optional cleanup, comments, and abstractions.
- **34:** Freeze features. Start broad validation.
- **40:** Stop debugging unless the build is broken. Begin ownership review.
- **43:** Start the close.

After 60-90 seconds without evidence, stop editing and run a discriminating check.

## Ownership Scan

- [ ] no accidental deletion or unrequested file
- [ ] no weakened/skipped/overfit test
- [ ] no hardcoding or swallowed error
- [ ] no `any`, unsafe cast, unchecked null, or ignored error false-fix
- [ ] no API, ordering, mutation, or serialization drift
- [ ] no unbounded work, retry, goroutine, queue, or memory growth
- [ ] no dead code or speculative abstraction
- [ ] final time and space complexity stated

## Closing Script

> I completed __. Each checkpoint passed __, and the final __ passed. The controlling
> path is __ time and __ space. I accepted/rejected the AI suggestion to __ because
> __. The remaining risk is __; the smallest next check would be __.

## Language Flash Scan

**Java:** null/overflow, mutation/order, `equals`/`hashCode`, broad exceptions,
interrupts, shared state.

**TypeScript/Node:** no `any` false-fix, awaited promises, rejection propagation,
runtime validation, module format, event-loop blocking, cleanup.

**Go:** nil/zero values, slice/map aliasing, ignored errors, contexts, goroutine exits,
channel ownership, map-order determinism.
