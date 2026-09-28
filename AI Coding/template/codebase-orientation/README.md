# Iterative Codebase Orientation Prompts

Run the prompts in order in the same interview conversation when possible. Each full
prompt is ready to send unchanged, and its quick version appears in the same file.

## Simple Implementation-Part Contract

> [!IMPORTANT]
> Plan mode returns **one complete response containing all slices in execution order**.
> A slice is simply a working part such as `Flow 1` or `Flow 2`.

| AI OUTPUT - every slice |
|---|
| `### <ID>: <flow or implementation part>` |
| `Change: <bounded behavior and likely files/symbols>` |
| `Check: <observable test or result>` |

After all slices and final validation, the final line of the **entire Plan response**
is `Plan self-check: PASS`.

### <span class="action-chip action-verify">VERIFY</span> Before Accepting a Plan

- [ ] You reviewed the AI's complete Plan response before approving it.
- [ ] All implementation parts are present at once and ordered sensibly.
- [ ] Every slice has a nonempty `Change` and `Check`.
- [ ] Every acceptance criterion maps to a slice and validation check.
- [ ] Full-suite-after-every-change rule is present.
- [ ] The entire response ends with `Plan self-check: PASS`; otherwise ask AI to rewrite it.

| Order | Mode | <span class="action-chip action-prompt">PROMPT TO AI</span> | <span class="action-chip action-output">AI OUTPUT</span> |
|---|---|---|---|
| 1 | Agent - research | [Architecture, flows, tests, class/method comment audit](01-architecture-and-flows.md) | `.interview/research/00-architecture-tests-and-comments.md` |
| 2 | Agent - research | [Bugs, unfinished work, gaps, risks](02-bugs-gaps-and-risks.md) | `.interview/research/01-bugs-gaps-and-risks.md` |
| 3 | Agent - research | [Verify and summarize](03-verify-and-summarize.md) | `.interview/research/02-orientation-summary.md` |
| 4 | Agent completes task note; rare discovery; then Plan | [Prepare a task file and choose a plan](04-plan-checkpoint.md) | `.interview/tasks/task_<id>.md`, then chat-only sliced plan |

*<span class="action-chip action-wait">WAIT</span> Complete and verify each output
before sending the next numbered prompt.*

Task-file templates: [bug](../checkpoint-task-files/bug.md),
[feature](../checkpoint-task-files/feature.md),
[optimization](../checkpoint-task-files/optimization.md), and
[enhancement/refactor](../checkpoint-task-files/enhancement-refactor.md).

## Mode Boundaries

> [!NOTE]
> <strong class="action-chip action-know">KNOW - MODE BOUNDARIES</strong>
> - Agent research: Prompts 1-3 may edit only `.interview/research/*.md`.
> - Agent task preparation: AI may edit only the current `task_<id>.md`.
> - Plan mode: asks questions and returns all ordered slices in one chat response; it
>   edits nothing.
> - Plan persistence: manually copy the complete accepted plan or use Prompt 4's
>   dedicated Agent persist-only turn; verify every slice before implementation.
> - Agent implementation: executes one persisted named slice, tests, updates Latest
>   Snapshot, reports, and stops without replacing Accepted Plan.

## Candidate vs. AI at a Glance

### <span class="action-chip action-do">DO YOURSELF</span>

1. Create the short task note and fill what you know.
2. Answer clarification questions if AI asks them.
3. Review the complete Plan response, request corrections if needed, then accept it.
4. Persist and verify the complete accepted plan and every slice.
5. Name one persisted slice ID in a separate Agent implementation turn.
6. Inspect the diff and test output; summarize the completed task to the interviewer.

| AI RESPONSIBILITY |
|---|
| Complete missing task-note context from evidence. |
| In Plan mode, ask questions and return all numbered implementation parts at once. |
| In a dedicated persist-only turn, copy the complete plan and make no project edits. |
| In Agent implementation, leave Accepted Plan unchanged and implement only the named slice. |
| Run all exposed tests, update Latest Snapshot, report completed/blocked, and stop. |

No separate ledger or manual slice-status bookkeeping is required.

## Choose One Input Method

### External Copy/Paste Allowed

For research Prompts 1-3:

#### <span class="action-chip action-do">DO YOURSELF</span>

1. Open the numbered prompt file.

#### <span class="action-chip action-prompt">PROMPT TO AI</span>

```text
Send the complete fenced text block unchanged.
```

*WAIT - let AI report the output path before continuing.*

#### <span class="action-chip action-verify">VERIFY</span><span class="action-chip action-know">KNOW</span>

- [ ] Open and verify the artifact; understand it before sending the next prompt.

For Prompt 4:

#### <span class="action-chip action-do">DO YOURSELF</span>

1. Assign an ID and copy the table-free task template.
2. Fill `Task` and known details; leave the rest `TO BE FILLED BY AGENT`.

#### <span class="action-chip action-prompt">PROMPT TO AI</span> Clear Task

```text
COMPLETE CURRENT TASK
```

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Task or acceptance is unclear</summary>

```text
DISCOVER UNCLEAR TASK
```

- [ ] VERIFY the Behavior Trace and resolve `AMBIGUOUS`.

</details>

#### <span class="action-chip action-do">DO YOURSELF</span> Form Your Direction First

Before Plan mode, spend 30-60 seconds deciding the acceptance condition, simplest
approach/flow order, and predicted first check. Do not delegate architecture.

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> "My current approach is `<approach/order>`. I expect `<check>` first; I will ask AI
> for a bounded plan and compare it with this direction."

#### <span class="action-chip action-prompt">PROMPT TO AI</span> Plan Mode

1. Send `CURRENT_TASK: <path>`.
2. Choose the task type and send its full prompt unchanged.
3. Answer clarification questions one at a time; Plan remains chat-only.

#### <span class="action-chip action-verify">VERIFY</span> Plan Contract

- [ ] The response contains all ordered slices, each with `Change` and `Check`.
- [ ] It was compared with your direction; deviations have code/requirement/test evidence.
- [ ] No unnecessary rewrite, hierarchy, nested class design, or abstraction remains.
- [ ] You reviewed aloud what matched, what looked off, and what you accepted/rejected.
- [ ] The final line of the entire response is `Plan self-check: PASS`.

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> State the accepted slice order and why.

#### Choose Exactly One Persistence Method

Do not use both methods.

#### <span class="action-chip action-prompt">PROMPT TO AI</span> Default: AI Copy

Use Prompt 4's `PERSIST ACCEPTED PLAN ONLY` prompt in a dedicated Agent turn. It may
change only the current task file, must report persisted slice IDs in order, and stops
without implementing.

#### <span class="action-chip action-do">DO YOURSELF</span> Alternative: Manual Copy

Use this only when manual copy is available and faster, or Agent mode cannot reliably
see the Plan response. Replace **Accepted Plan** with the complete final response. Do
not run AI Copy afterward.

#### <span class="action-chip action-verify">VERIFY</span> Persistence Gate

- [ ] The final plan, not a summary, is under **Accepted Plan**.
- [ ] Every accepted slice appears exactly once and in order with `Change` and `Check`.
- [ ] No source, test, configuration, or build file changed.

#### <span class="action-chip action-prompt">PROMPT TO AI</span> Agent Mode

Only after the gate passes, start a separate turn and name exactly one persisted slice
ID using Prompt 4's execution prompt. It must not replace or summarize Accepted Plan.

### External Copy/Paste Prohibited

#### <span class="action-chip action-prompt">PROMPT TO AI</span>

Open the same numbered file and type its `Quick Prompt`. For Prompt 4, prepare the task
note, run the clear or rare prompt, form and state your own direction, send
`CURRENT_TASK`, switch to Plan mode, and type the matching task Quick Prompt. Use
Prompt 4's persist-only Agent prompt by default; manually enter the accepted plan only
if Agent cannot reliably persist it. Never do both.

#### <span class="action-chip action-verify">VERIFY</span> Before Continuing

- [ ] Review the complete AI response before accepting it.
- [ ] Verify every accepted slice is persisted before naming one for implementation.

> [!NOTE]
> <strong class="action-chip action-know">KNOW - TEST RULE</strong>
> After every code/test change, Agent runs every exposed test before another edit and
> records hidden-test limitations.

> [!NOTE]
> <strong class="action-chip action-know">KNOW - QUICK PROMPT RULES</strong>

1. **ORDER:** type every numbered line in order.
2. **NO_OMISSION:** omit no numbered line.
3. **NO_COMBINE:** never combine P1, P2, P3, or P4.
4. **DRIFT:** reject any action not numbered or performed after `stop`.

> [!NOTE]
> <strong class="action-chip action-know">KNOW - DIAGRAM POLICY</strong>

- Prompt 1 requires architecture, low-level-design, and primary-flow diagrams.
- Prompt 3 requires one final architecture diagram.
- Prompt 2 requests a diagram only when relationships are materially easier to
  understand visually than in a table or short ordered list.
- Whenever a diagram is included, every code component in it must be grounded by a
  Markdown hyperlink to an existing repository file.

All artifacts are intentionally bounded for interview reading: Pass 1 is at most 180
lines; Passes 2 and 3 are at most 100 lines. Each starts with a short scan-first
briefing and favors compact tables over prose. Plan limits are task-specific: bug fix
60, feature 90, optimization 80, enhancement/refactor 75 lines.

## Parallelism Rule

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Rare unclear-task discovery only</summary>

### <span class="action-chip action-prompt">PROMPT TO AI</span>

Send one prompt to the main Agent; do not look for a platform subagent control. The
parent may spawn at most two read-only workers, reconciles their evidence, and remains
the only writer. Never parallelize edits, dependent slices, or overlapping files.

</details>
