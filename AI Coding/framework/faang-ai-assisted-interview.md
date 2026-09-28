# FAANG AI-Assisted Coding Interview Framework

## Purpose

This playbook targets a 45-minute Senior SWE interview in an existing, multi-file
repository. The round may reveal two to five dependent or independent checkpoints,
including bug fixes, features, performance work, and enhancements.

The goal is not to demonstrate maximal AI usage. The goal is to produce correct,
complete, explainable, and tested changes faster while retaining engineering
ownership.

> Operating principle: treat AI output, interviewer hints, and visible tests as
> hypotheses. Requirements, code, and executable evidence decide what is true.

> [!IMPORTANT]
> [AI coding basics](../basics.md) and [AI coding mistakes](../mistakes.md) are the
> controlling interaction guidance for this playbook. When another workflow detail
> conflicts with them, candidate ownership, visible review, and verification win.

No public framework can guarantee coverage of undisclosed company scorecards. This
framework maps every criterion found in the local preparation material and verified
public guidance to observable interview behavior.

## Success Definition

By minute 45, the candidate should have:

- created a grounded repository research pack under `.interview/research/`;
- maintained one `.interview/tasks/task_<id>.md` scratchpad per checkpoint containing
   its current context, accepted plan, and latest implementation/validation snapshot;
- completed every required checkpoint;
- preserved behavior from earlier checkpoints;
- run every available test after each code or test change before making another;
- run the broadest available regression check;
- explained correctness, complexity, tradeoffs, and residual risk;
- reviewed and understood every retained AI-generated change; and
- made one memorable senior-level signal: a visible chain from each requirement to
  an invariant, implementation decision, and test result.

## Rubric Contract

### Primary observable areas


| Evaluation area                    | What the interviewer must observe                                                                                                        | Required evidence                                                  |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| Problem Solving                    | Clarifies acceptance criteria, identifies invariants and edge cases, orders dependencies, compares realistic approaches                  | Task files and explicit implementation order                       |
| Code Development and Understanding | Finds the exact code path that controls the requested behavior, follows local patterns, preserves contracts, makes minimal coherent changes, explains existing and generated code | Integrated working code with no unexplained region                 |
| Verification and Debugging         | Predicts behavior, reproduces or characterizes failures, diagnoses causes, and runs all exposed tests after every change                 | Full exposed suite after each change plus focused evidence         |
| Technical Communication            | States intent before acting, reports decisions and results, incorporates feedback, and explains pivots                                   | Concise updates at decision boundaries and an evidence-based close |

### Cross-cutting areas


| Evaluation area        | What the interviewer must observe                                                                                 | Required evidence                                                                   |
| ---------------------- | ----------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| CS Fundamentals        | Correctness reasoning, suitable data structures, complexity, boundaries, and concurrency reasoning where relevant | Correctness argument and final time/space complexity                                |
| AI Fluency             | Bounded delegation, useful context, critical review, drift detection, and knowing when direct coding is faster   | No AI change accepted without inspection and validation                             |
| Judgment and Ownership | Explicit tradeoffs, evidence-based disagreement, minimal scope, and responsibility for all code                   | Every accept, reject, or pivot tied to a requirement, invariant, code fact, or test |
| Completion and Time    | Hard time gates, fast checkpoint handoff, and deliberate scope control                                            | All required implementation complete by minute 34                                   |

Passing tests alone do not satisfy the rubric. The candidate must make the reasoning
and verification process observable.

## Human-First AI Loop

Use this loop for every AI interaction:

1. <span class="action-chip action-do">THINK</span> Decide your intent, provisional approach, and predicted useful result
   before prompting.
2. <span class="action-chip action-say">SAY</span> Tell the interviewer what you are about to ask AI to do and why.
3. <span class="action-chip action-prompt">PROMPT</span> Delegate one bounded task; keep architecture and strategy human-owned.
4. <span class="action-chip action-verify">REVIEW ALOUD</span> Read the response or every changed line, state what matches,
   flag what is wrong or surprising, and accept or reject it explicitly.
5. <span class="action-chip action-verify">VERIFY</span> After every code or test change, run the available code/tests and
   inspect the result before another edit, prompt, slice, or phase.

Never build on unreviewed AI output. A passing test does not replace understanding the
generated code.

## 45-Minute State Machine


| Time        | State                   | Required outcome                                                        | Exit gate                                                   |
| ----------- | ----------------------- | ----------------------------------------------------------------------- | ----------------------------------------------------------- |
| 0:00-0:30   | Start                   | Checkpoint release style and pre-existing repository changes confirmed  | Starting conditions are clear                               |
| 0:30-7:00   | Agent mode: research    | Three grounded research artifacts created; no project files changed      | Architecture, flows, quality, and tests are understood      |
| 7:00-9:00   | Task note, human direction, Plan, persistence | Candidate states a simple approach before AI; all accepted slices are persisted | Persistence gate passes; candidate names the first slice |
| 9:00-34:00  | Agent mode: implement   | Approved task implemented and validated after every change               | All required checkpoints are complete                       |
| 34:00-40:00 | Agent mode: integrate   | Broad suite/typecheck/build is green; regressions repaired               | Integrated behavior is validated                            |
| 40:00-43:00 | Own                     | Final changed regions and complexity reviewed                           | Candidate can defend every retained change                  |
| 43:00-45:00 | Close                   | Results, tradeoffs, AI judgment, and risk summarized                    | Interviewer has explicit evidence for each rubric           |

### Checkpoint budgets

Each checkpoint budget includes implementation, review, and focused validation.


| Number of checkpoints | Budgets from minute 9 to minute 34 | Total      |
| --------------------- | ---------------------------------- | ---------- |
| 2                     | 13 + 12 minutes                    | 25 minutes |
| 3                     | 9 + 8 + 8 minutes                  | 25 minutes |
| 4                     | 7 + 6 + 6 + 6 minutes              | 25 minutes |
| 5                     | 5 + 5 + 5 + 5 + 5 minutes          | 25 minutes |

Reallocate only when an early checkpoint is genuinely foundational. Keep these hard
gates:

- first green checkpoint around minute 19 or earlier;
- at least half of the checkpoints complete by minute 26;
- all required implementation complete by minute 34;
- no optional polish after minute 30; and
- no new features after minute 34.

## Phase 1: Confirm Starting Conditions (0:00-0:30)

### <span class="action-chip action-know">KNOW</span> Fixed Environment

This playbook assumes the interview environment always provides an initialized Git
repository and an AI assistant that can search, read, edit, run commands, and call
the available tools. Model switching is also available. These are fixed facts, so do
not spend interview time checking them or inventing alternatives for unavailable tools.

**Framework rationale:** treat published environment capabilities as fixed inputs,
not hypothetical decision branches. Branch only on facts that actually vary, such as
whether checkpoints arrive together and whether starter files already contain
changes. This avoids spending time preparing for conditions that cannot occur.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Checkpoint Release

> "Will you show me all checkpoints now, or reveal them one at a time?"

### <span class="action-chip action-do">DO YOURSELF</span> Inspect Starter Changes

1. Run `git status --short` before editing.

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Only when Git is not clean</summary>

> <strong class="action-chip action-say">SAY TO THE INTERVIEWER</strong>
> "These files were already modified before I started. Should I preserve them as
> part of the starter code?"

</details>

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Opening Narration

> I am going to take a couple of minutes to understand the requirements and controlling
> code paths before changing anything. I will state my intent before each AI prompt,
> review its output aloud, and run the available tests after every code or test change
> before moving on.

Do not spend interview time creating elaborate AI configuration or project
scaffolding unless the task explicitly requires it.

### <span class="action-chip action-know">KNOW</span> Mode Strategy

Use modes according to the kind of thinking required:

1. **Agent mode - research (0:30-7:00):** use repository search, reads, and tools to
   build the research pack. Its write scope is only `.interview/research/*.md`.
   Source comments, source code, tests, configuration, and build files are read-only.
2. **Agent mode - task preparation:** create the table-free
   `.interview/tasks/task_<id>.md`, fill known details, and mark the rest
   `TO BE FILLED BY AGENT`. For the normal clear task, AI completes only that note.
   Use parallel discovery only in the rare unclear case.
3. **Candidate direction:** before asking AI to plan, state the acceptance condition,
   simplest likely approach/part order, and predicted first check.
4. **Plan mode (7:00-9:00):** consume the current task file. Choose the matching
   bug-fix, feature, optimization, or refactor prompt. Produce a task-appropriate
   sliced plan; edit no files.
5. **Plan persistence:** after accepting the plan, persist every slice under
   **Accepted Plan**, manually or in a dedicated Agent persist-only turn. Verify the
   complete copy before any source/test edit.
6. **Agent mode - implementation (9:00-34:00):** explicitly name one persisted slice
   ID, implement only it, test after every change, replace **Latest Snapshot**, and stop.
7. **Agent mode - integration (34:00-40:00):** run broad checks and make only
   correctness, build, or regression fixes.

Do not remain in Agent mode merely because it can plan. Plan mode creates a clearer
decision record; Agent mode is reserved for repository research, plan persistence,
and approved edits.

## Phase 2: Full-Codebase Orientation (0:30-7:00)

### <span class="action-chip action-know">KNOW</span> Orientation Scope

Do not analyze the checkpoint yet. First understand the repository as a system. Here,
**full-codebase orientation** means:

- identify every first-party top-level module or service and its responsibility;
- understand the high-level architecture and the important low-level classes,
  interfaces, functions, and data structures;
- trace the primary success, error, data, event, persistence, and asynchronous flows;
- identify every component participating in those flows;
- inventory build commands, tests, and visibly incomplete test coverage; and
- audit existing comments on critical or large classes and methods, proposing improvements only
   inside the research artifact; and
- record observed bugs, unfinished code, gaps, risks, and conflicting behavior.

Exclude dependencies, generated files, build output, and line-by-line inventories.
Cover the whole first-party repository breadth-first, then add detail for its primary
runtime flows. This is repository orientation, not task analysis.

### <span class="action-chip action-output">AI OUTPUT</span> Research Artifacts

All research must be written under this repository-relative folder:

```text
.interview/research/
   00-architecture-tests-and-comments.md
   01-bugs-gaps-and-risks.md
   02-orientation-summary.md
```

Each research pass writes or updates only its assigned Markdown file. Every research
file is the durable result of that pass. Research is not complete while it exists
only in chat. During this phase, no file outside `.interview/research/` may change.

### <span class="action-chip action-do">DO YOURSELF</span> Choose the Prompt Input Method

Use the [orientation prompt index](../template/codebase-orientation/README.md). Each
pass has two distinct candidate actions: **submit the prompt** and **understand the
saved output**. Finish both before moving to the next pass.

Choose one input method once:

- **External copy/paste allowed:** send each numbered full prompt unchanged. The
   research prompts discover the repository, languages, and prior artifacts. Prompt
   4 establishes explicit or implicit checkpoint context, then plans it.
- **External copy/paste prohibited:** open the same numbered file and type its
   self-contained `Quick Prompt` in the same chat. No separate setup prompt is needed.

Do not edit or customize either fixed prompt form. The short task-note values and
`CURRENT_TASK` path are the only dynamic inputs.

#### Pass 1: Understand architecture, flows, tests, and critical code (0:30-4:15)

##### <span class="action-chip action-prompt">PROMPT TO AI</span>

In Agent mode, send Prompt 1 unchanged or type its same-file Quick Prompt.

##### <span class="action-chip action-wait">WAIT</span>

Wait until AI reports that it wrote
`.interview/research/00-architecture-tests-and-comments.md`. Do not send Prompt 2 yet.

##### <span class="action-chip action-verify">VERIFY</span>

- [ ] Artifact is at most 180 lines and is not repetitive; otherwise ask AI to compress.
- [ ] Representative links support flow entry, business logic, exit, runner, and test claims.
- [ ] Test assertions support the claimed coverage and reveal weak/untested paths.
- [ ] `git diff` shows only the research Markdown file changed.
- [ ] Existing comments on every critical or large class/method are accurately
      classified `ADEQUATE`, `NEEDS_ENHANCEMENT`, or `MISSING`.

##### <span class="action-chip action-know">KNOW</span>

> Be able to explain every top-level module's job; runtime entry/storage/external
> boundaries; each primary flow's trigger, components, data/error path, and result;
> important LLD symbols/contracts; and focused/broad validation methods.

##### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span>

> "The system starts at __, the main components are __, the primary flow is __, and
> validation uses __."

#### Pass 2: Understand bugs, unfinished work, gaps, and risks (4:15-5:30)

##### <span class="action-chip action-prompt">PROMPT TO AI</span>

In Agent mode, send Prompt 2 unchanged or type its same-file Quick Prompt.

##### <span class="action-chip action-wait">WAIT</span>

Wait until `.interview/research/01-bugs-gaps-and-risks.md` is written.

##### <span class="action-chip action-verify">VERIFY</span>

- [ ] Artifact is at most 100 lines and does not repeat architecture/test inventory.
- [ ] Top findings link to evidence.
- [ ] Every observed bug proves actual behavior and the violated contract/test/schema.

##### <span class="action-chip action-know">KNOW</span>

> Distinguish `BUG`, `UNFINISHED`, `GAP`, `RISK`, and `UNKNOWN`; know which findings
> affect primary flows or constrain later changes.

##### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span>

> State the most important observed issue and the highest unproven risk.

#### Pass 3: Verify and summarize orientation (5:30-7:00)

##### <span class="action-chip action-prompt">PROMPT TO AI</span>

In Agent mode, send Prompt 3 unchanged or type its same-file Quick Prompt.

##### <span class="action-chip action-wait">WAIT</span>

Wait until `.interview/research/02-orientation-summary.md` is written.

##### <span class="action-chip action-verify">VERIFY</span>

- [ ] Summary is at most 100 lines and is not repetitive.
- [ ] It reports zero broken evidence links and no unresolved contradictions.
- [ ] Every top-level module and primary flow appears in the indexes.

##### <span class="action-chip action-know">KNOW</span>

> Understand the final architecture diagram, test posture, critical findings,
> contracts/invariants, and remaining unknowns.

##### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span>

> State purpose, components, one primary flow, validation methods, strongest coverage
> gap, highest material risk, and contracts the checkpoint must preserve.

### <span class="action-chip action-verify">VERIFY</span> Orientation Gate

- [ ] All three files exist and meet their line budgets.
- [ ] Sampled links support their claims.
- [ ] Summary covers all top-level modules and primary flows.
- [ ] No project file changed.
- [ ] Contradictions are corrected or explicitly `UNKNOWN`.

## Phase 3: Establish Context and Plan the Checkpoint (7:00-9:00)

The checkpoint may be explicit ("fix this bug") or implicit (only a failing test,
diagnostic, stub, example mismatch, or benchmark regression is visible).

### <span class="action-chip action-do">DO YOURSELF</span> Create the Task Note

1. Create `.interview/tasks/task_<id>.md` from the table-free
   [bug](../template/checkpoint-task-files/bug.md),
   [feature](../template/checkpoint-task-files/feature.md),
   [optimization](../template/checkpoint-task-files/optimization.md), or
   [enhancement/refactor](../template/checkpoint-task-files/enhancement-refactor.md)
   template. Fill `Task` and anything obvious; mark the rest
   `TO BE FILLED BY AGENT`. Budget under 30 seconds.

### <span class="action-chip action-prompt">PROMPT TO AI</span> Complete Clear-Task Context

```text
COMPLETE CURRENT TASK
```

### <span class="action-chip action-output">AI OUTPUT</span> Completed Task Note

Agent reads focused code/tests, replaces placeholders with grounded values or
`UNKNOWN`/`NOT_AVAILABLE`, and sets `CONTEXT_READY`. It must not rediscover, broaden,
or implement the explicit task.

### <span class="action-chip action-verify">VERIFY</span> Task Note

- [ ] Task and acceptance match the interviewer request.
- [ ] Evidence links support the relevant code/path and invariants.
- [ ] Status is `CONTEXT_READY`; no Behavior Trace is required for a clear task.

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Rare: Task or Acceptance Is Unclear</summary>

Only now spend at most 60-90 seconds on Prompt 4's `DISCOVER UNCLEAR TASK`. You send
one prompt:

```text
DISCOVER UNCLEAR TASK
```

The parent AI may internally spawn up to two read-only Signal/Contract and Code-Path
workers, reconcile them, or perform both passes itself when spawning is unavailable.

The parent uses an observation ladder with no command requirement: existing output,
test/build button, manual UI/API/sample flow, diagnostics, static evidence, or
`NOT_AVAILABLE`. It writes one Behavior Trace line:

`SIGNAL -> EXPECTED SOURCE -> ENTRY -> RELEVANT PATH -> EXACT GAP`

### <span class="action-chip action-verify">VERIFY</span> Unclear-Task Evidence

- [ ] Trace has `SIGNAL -> EXPECTED SOURCE -> ENTRY -> RELEVANT PATH -> EXACT GAP`.
- [ ] Cited files/symbols support the proposed change location.
- [ ] Candidate task and acceptance are unambiguous.

If the parent cannot resolve the task from at most three candidates, it sets
`AMBIGUOUS`.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> Resolve Ambiguity

> I see `<test/error/stub>`. Evidence points to `<candidate task>`, with success
> defined as `<acceptance>`. Is that the intended checkpoint and scope?

Record the answer in the task file and set it to `CONTEXT_READY`. This file is the
concrete Plan input; do not rely on vague chat history.

</details>

### <span class="action-chip action-do">DO YOURSELF</span> Choose the Task Type

Choose exactly one variant:
   - bug fix: incorrect existing behavior;
   - feature: new observable behavior;
   - optimization: equivalent behavior with better measured performance;
   - enhancement/refactor: structural or compatibility change.

### <span class="action-chip action-do">DO YOURSELF</span> Form Your Direction Before AI

Spend 30-60 seconds forming a provisional human plan before requesting an AI plan:

1. Restate the acceptance condition.
2. Choose the simplest likely approach and part/flow order using existing code and
   helpers where possible.
3. Predict the first check that should pass.

Do not ask AI to choose the architecture or strategy for you. Its plan is a draft to
compare against this direction, not the starting point for your reasoning.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> State Intent Before Prompting

> "My current approach is `<simple approach>` in `<part order>`. I expect `<check>`
> to prove the first part. I will compare AI's bounded plan against this direction."

### <span class="action-chip action-prompt">PROMPT TO AI</span> Request the Plan

1. Switch to Plan mode.
2. Send `CURRENT_TASK: .interview/tasks/task_<id>.md`.
3. Send the selected full or Quick Prompt unchanged.

If context is absent, conflicting, or ambiguous, AI
   asks up to three concise questions in conversation, one at a time. Answer normally;
   Plan mode uses each answer in chat and continues without editing files. The separate
   persistence step stores the clarified context with the complete accepted plan.

<details>
<summary><strong class="action-chip action-optional">OPTIONAL</strong> Questions for the Interviewer</summary>

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span>

1. Copy the `UNKNOWNS` from the context and Plan response.
2. Check the task wording, failure output, tests, public API/schema, and research. Drop
   every question those sources answer.
3. If an answer would not change code or acceptance, do not ask.
4. If a conventional default is reversible in under one minute, state that assumption
   aloud and continue.
5. Otherwise ask one direct question, record the answer, then ask the next. Ask at
   most three before accepting the plan.

| Type | Ask this when unresolved |
|---|---|
| Bug fix | "Test `<name>` expects `<A>`, code returns `<B>`. Is `<A>` required for all `<scope>`, or only this case?" |
| Feature | "When `<conditions>` conflict, which wins? Must current callers/output remain compatible?" |
| Optimization | "Which workload, metric, and target define success? Which output/error/order semantics must remain identical?" |
| Enhancement/refactor | "Which API and behavior must remain unchanged? Is migration, backfill, or compatibility handling required?" |

Ask about security, concurrency, transactions, persistence, cancellation, or external
failures only when the affected path uses them.

</details>

### <span class="action-chip action-know">KNOW</span> What a Slice Means

A **slice** is one numbered implementation part. Plan mode returns **all slices at
once in one complete response**, in execution order. A small task uses one slice; a
large scope may use `Flow 1`, then `Flow 2`. Split by working behavior, not code layers.


> [!IMPORTANT]
> **EACH SLICE IS SHORT**
> - `### <ID>: <flow or implementation part>`
> - `Change: <bounded behavior and likely files/symbols>`
> - `Check: <observable test or result>`
>
> After all slices and final validation, the final line of the **entire Plan-mode
> response** is `Plan self-check: PASS`.
>
> No prompt gives an absolute model guarantee. Enforcement has three layers: fixed
> schema, AI self-check/rewrite, and candidate verification/rejection.

### <span class="action-chip action-know">KNOW</span> Check Invariants During Plan Review

An invariant matters **before execution** because it is the behavior the selected
slice must not break. Prompt 4 identifies the task-relevant invariants and preserving
checks. Review them now; do not pause an already-running Agent turn to rediscover them.

Use evidence from explicit requirements, passing tests, public API/schema/error
contracts, or data/state rules. For optimization, require equivalent outputs, errors,
ordering, mutation, and side effects.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> State the Key Invariant

> `<Invariant>` must remain true; `<test/contract>` proves it; slice `<ID>` preserves
> it through `<change>`.

### <span class="action-chip action-verify">VERIFY</span> Plan Before Accepting

This means reviewing the AI's complete Plan-mode response before you approve or
persist it.

- [ ] Plan fits its cap: bug 60, feature 90, optimization 80, refactor 75 lines.
- [ ] All slices are present at once, ordered by working flow or implementation part.
- [ ] Every slice has a bounded `Change` and a proving `Check`.
- [ ] Every acceptance criterion maps to a slice/check.
- [ ] Full-suite-after-every-change rule is present.
- [ ] The response was compared with the stated human direction; every deviation is
   accepted only when code, requirements, or test evidence supports it.
- [ ] It uses the simplest repository-consistent design; no unnecessary hierarchy,
   nested class structure, abstraction, or rewrite was accepted.
- [ ] Optional dependencies, rollback, migration, benchmark, concurrency, or security
      sections appear only when relevant.
- [ ] The final line of the entire Plan response is `Plan self-check: PASS`.

Ask AI to rewrite any plan that fails a checkbox.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> State the Plan

> "The implementation parts are `<IDs>` in this order. Each part has a bounded change
> and a check before I move to the next one."

### <span class="action-chip action-know">KNOW</span> Persistence Is a Hard Gate

> The final accepted plan, including every generated slice, must be present under
> **Accepted Plan** in `task_<id>.md` before any source/test edit.

### Choose Exactly One Persistence Method

Do **not** perform both methods.

### <span class="action-chip action-prompt">PROMPT TO AI</span> Default: AI Copy

Use this when Agent mode can read the Plan response and write the task file:

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

Use this when manual copy is available and faster, or Agent mode cannot reliably see
the Plan response. Copy the complete final response into **Accepted Plan**, replacing
the old plan. Do not run the AI-copy method afterward.

### <span class="action-chip action-verify">VERIFY</span> Persistence Gate

- [ ] Accepted Plan contains the final plan, not a summary.
- [ ] Every generated slice ID appears exactly once and in accepted order.
- [ ] Every slice retains its nonempty `Change` and `Check`.
- [ ] Accepted optional fields, test rules, final validation, complexity/risk, and
   `Plan self-check: PASS` are present.
- [ ] Persistence changed no source, test, configuration, or build file.

Repair any failure before implementation. A replan repeats this entire gate.

### <span class="action-chip action-verify">VERIFY</span> Ready for Phase 4

- [ ] The complete accepted plan and all slices are persisted.
- [ ] The slices' `Change`, `Check`, and key preserving invariants are understood.
- [ ] No source or test edit occurred during planning or persistence.

For a progressive checkpoint, establish its context and return to Plan mode. Update a
research artifact only when new evidence proves it wrong; never rebuild the pack.

## Phase 4: Execute Persisted Slices (9:00-34:00)

### <span class="action-chip action-know">KNOW</span> Implementation Boundary

Run the same loop for every task.

Phase 3 may have used a persist-only Agent turn; that turn stopped without coding.
Now start the first **implementation** Agent turn. Its write scope is the current task
file plus source/test files named in the selected slice. If the accepted plan is
absent, stale, or missing any slice, do not edit project files; return to the
persistence gate. Do not implement any unrequested slice, reopen task discovery, or
restart broad research.

### <span class="action-chip action-know">KNOW</span> Progress Record

No separate ledger or manual slice-status bookkeeping is required. The Agent-owned
**Latest Snapshot** in `task_<id>.md` is the progress record.

### <span class="action-chip action-do">DO YOURSELF</span> Select One Slice

1. Verify every accepted slice is persisted in `task_<id>.md`.
2. Choose exactly one persisted slice ID.

### <span class="action-chip action-say">SAY TO THE INTERVIEWER</span> State Execution Intent

> "I am asking AI to implement only `<ID>` because `<reason>`. I expect `<check>` to
> pass, and I will review every changed line and test result before continuing."

### <span class="action-chip action-prompt">PROMPT TO AI</span> Execute One Slice

```text
Execute only slice <ID> from CURRENT_TASK.
The complete accepted plan is already persisted; do not replace or summarize it.
Do not start another slice.
After every code or test change, run all available test cases before another change.
Update Latest Snapshot. Report completed or blocked, then stop.
```

### <span class="action-chip action-know">KNOW</span> Agent Responsibilities

1. Verifies the named slice exists in the persisted Accepted Plan; otherwise stops.
2. Edits only files/behavior belonging to the named slice.
3. After every code or test change, runs all available tests before another edit. If
   tests fail, it preserves output, diagnoses the failure, and stays in this slice.
4. Reviews the changed region for requirements, APIs, types, errors, complexity, and
   concurrency concerns.
5. Replaces **Latest Snapshot**, reports `completed` or `blocked`, and stops.

### <span class="action-chip action-output">AI OUTPUT</span> Latest Task Snapshot

This is produced **inside the same execution turn above**, just before Agent mode
stops. It is not another prompt or a pre-coding step. It records current status,
changed files/behavior, validation results, remaining work, and risk/complexity.

### <span class="action-chip action-verify">VERIFY</span> After Agent Mode Stops

1. Read every changed line and inspect the actual test output; do not trust the
   summary alone.
2. Review aloud: state what matched the request, flag anything wrong or surprising,
   and say which generated changes you accept, revise, or reject.
3. Confirm **Latest Snapshot** matches the actual files, tests, remaining work, and risk.
4. Do not send another implementation prompt or begin another slice until the retained
   code is understood and every exposed test result is green or explicitly explained.
5. If blocked, keep the same slice and use the debugging prompt. If evidence invalidates
   the plan, return to Plan mode. Do not start another slice.
6. Before any pivot, tell the interviewer what evidence changed your mind and why the
   next approach is better.
7. If completed and another slice remains, start a new Agent turn naming that slice.
8. If this was the final slice, perform the task closeout below.

If evidence invalidates remaining slices, return to Plan mode and revise only the
unfinished part of the plan. Do not silently improvise a new implementation path.

Suggested handoff:

> T2 is complete: the new error path is covered by the focused test, and the T1 tests
> still pass. The implementation remains linear. I can take the next checkpoint.

### Type-Specific Completion Checks

These are not another loop and require no manual status bookkeeping. Agent mode checks
the relevant list while implementing; you verify its evidence before declaring the
task complete.

#### Bug fix

1. Reproduce the failure or characterize it with a concrete input.
2. State one falsifiable root-cause hypothesis.
3. Choose the cheapest check that could disprove the hypothesis.
4. Add or identify a regression test.
5. Make the smallest root-cause repair.
6. After every code/test change, run the focused test and all available tests before
   another edit.

Do not combine the fix with cleanup unless cleanup is necessary for correctness.

#### Feature

1. Define input, output, error, ordering, and compatibility contracts.
2. Identify the thinnest end-to-end path through the existing architecture.
3. Preserve public APIs unless the requirement explicitly changes them.
4. Cover the happy path, a boundary, and a failure path.
5. After every code/test change, run all available tests before another edit.

#### Performance optimization

1. Establish current complexity or obtain a reproducible baseline.
2. Name the specific bottleneck and target.
3. State which semantics must remain unchanged.
4. Optimize the controlling path without unrelated rewrites.
5. Compare before and after using complexity or measurements.
6. After every code/test change, run all available correctness tests before another
   edit, then repeat the measurement.

Passing tests proves compatibility, not improved performance. The optimization needs
its own evidence.

#### Enhancement or refactor

1. Characterize current observable behavior.
2. Protect that behavior with existing or focused tests.
3. Change one class or module responsibility at a time.
4. Avoid speculative abstractions for possible future checkpoints.
5. After every code/test change, run all available tests before another edit.

### After the Task Is Done

**Agent mode does this before stopping the final slice:**

1. Runs the full exposed test suite and any separate build/typecheck once more.
2. Confirms every acceptance criterion and invariant has evidence.
3. Replaces **Latest Snapshot** with `COMPLETED`, changed files, validation results,
   complexity, remaining limitations, and residual risk.

**Candidate (you), after Agent stops:**

1. Review the final diff and test output.
2. If anything is unexplained or failing, keep working on the same task; do not call it
   complete.
3. Give this spoken summary to the interviewer: "Task `<ID>` is complete.
   `<acceptance>` now works. I changed
   `<files/behavior>`. `<full-suite result>` passed. Complexity is `<...>`; residual
   risk is `<...>`."
4. If another checkpoint exists, create its `task_<id>.md` and repeat. Otherwise move
   to the integration phase.

## AI Control Protocol

### Human-owned decisions

The candidate owns:

- the provisional approach before any planning prompt;
- requirement interpretation and acceptance criteria;
- architecture, algorithms, data structures, and invariants;
- tradeoffs and task ordering;
- whether a generated patch is retained; and
- final correctness and explanation.

Good AI assignments include bounded repository search, repetitive edits,
boilerplate, test enumeration, unfamiliar syntax, and ranked debugging hypotheses.
Do the work manually when it takes less than roughly one minute or when prompting
plus review would cost more.

AI may challenge or detail the candidate's plan, but it does not choose the architecture.
Prefer an existing helper or a direct conditional over a new hierarchy, nested class
design, or abstraction unless the requirement and repository structure justify it.

### Parent-Agent parallelism

Use this for the rare unclear-task path, or for an unusually valuable independent
review after a stable slice. You send one prompt to the main AI Agent; you do not need
platform controls for subagents. That prompt tells the parent to internally spawn up
to two read-only workers when this saves time:

- **Signal/Contract worker:** identifies the observed/requested behavior and source of
   expected behavior.
- **Code-Path worker:** follows the relevant entry point, calls, and state transitions.
- If internal spawning is unavailable, the parent performs both passes sequentially
   without asking you to coordinate them.
- The parent verifies/reconciles both outputs and is the only writer. Source edits,
   dependent slices, and overlapping files are never parallelized.
- After a slice is stable, the same parent prompt may internally parallelize
   independent read-only test/review work, then perform one integration check.

### Fixed implementation prompts

These prompts use the current task file, accepted Plan-mode plan, code, and
terminal output already in context. Send them unchanged; do not fill a template.

Implementation:

```text
Read CURRENT_TASK and the accepted Plan-mode response. If the accepted plan
is absent, stale, incomplete, or missing the named slice, do not edit project files;
report that the complete plan must be persisted first, then stop. Do not replace or
summarize Accepted Plan in this implementation turn. Implement only the slice ID named
by the candidate; do not start another slice. After every code
or test change, run all available test cases before making another change. Use the full
platform Run Tests/Build control when that is the available runner; record any hidden
or unavailable test limitation. Preserve contracts and prior behavior. Replace Latest
Snapshot with status, change summary, files, validation/result, remaining work, and
risk/complexity. Report completed or blocked, then stop.
```

Debugging:

```text
Use the current failure output, changed code, and accepted plan. Do not edit yet.
Return at most three ranked root-cause hypotheses, evidence for each, and the cheapest
check that distinguishes them.
```

Final review:

```text
Review only current changes against the checkpoint analyses and repository contracts.
Flag correctness, edge-case, API, type, error, concurrency, regression, and complexity
risks. Reject weakened tests and unrelated refactors. Do not edit; rank findings.
```

### <span class="action-chip action-know">KNOW</span> AI Spiral Stop Conditions

Stop using AI for the current slice after:

- two incorrect attempts;
- uncertainty followed by an unsolicited rewrite, restructuring, or "start over" plan;
- repeated requirement or API drift;
- deletion or weakening of tests;
- a false fix such as hardcoding, swallowed errors, or unsafe typing; or
- output too large to verify within the checkpoint budget.

Return to the invariant, create a minimal probe, and continue manually. Switching
models is rarely worth the context and review cost during a 45-minute round.

Before redirecting, tell the interviewer: what AI got wrong, which evidence rejected
it, and what smaller direct step you will take instead.

### Safe pipelining

While the assistant generates, explain the already selected approach or inspect a
previously generated bounded change. Do not manually maintain a separate ledger and
never build on unreviewed output. Parallel activity should eliminate idle time, not
create parallel branches of unverified code.

## Adversarial and Unreliable Environment Protocol

### Unreliable coding assistant

Treat every response as an untrusted patch:

1. Compare changed scope with the accepted plan in the current task file.
2. Inspect additions and deletions.
3. Check API, type, errors, complexity, security, and concurrency semantics.
4. Predict a check result.
5. Compile or test before building on the patch.

If the assistant begins proposing rewrites instead of explaining the failure, say:

> This changes more than the failing invariant requires. I am discarding it, reducing
> the case, and testing the controlling branch directly.

### <span class="action-chip action-know">KNOW</span> Nerfed AI Fallback

If AI provides only hints, incomplete answers, cryptic output, or refusals, stop
depending on it for the hard reasoning. Use it only for boilerplate, unfamiliar
syntax, or basic scaffolding that you can fully review. Choose the algorithm,
architecture, debugging hypothesis, and final code path yourself. Do not spend the
interview repeatedly re-prompting or switching models for a solution.

### Misleading interviewer pushback

Treat pushback as a hypothesis, not an instruction to obey blindly:

1. Restate the suggestion to confirm understanding.
2. Test it against the stated requirement, invariant, or a counterexample.
3. Accept it when the evidence supports it.
4. Disagree calmly when it violates the contract.

Suggested response:

> Let me test that against the ordering requirement. With option A, input X returns
> Y, which violates the stated tie-breaker. I suggest option B because it preserves
> that invariant. If the intended requirement has changed, I will record that delta
> and adapt.

This is not stubbornness. The positive signal is updating quickly when evidence or
an explicit requirement change justifies it.

### Sparse hidden tests or weak platform feedback

Visible green tests are necessary but insufficient. Cover these classes manually or
with focused tests:

- empty, null, or missing input where the language permits it;
- minimum, maximum, overflow, and off-by-one boundaries;
- duplicates, ties, ordering, and determinism;
- mutation and aliasing;
- invalid input and partial failure;
- repeated calls and state leakage;
- concurrency, cancellation, and cleanup when applicable; and
- time, environment, filesystem, and network assumptions.

Spend at most 60 seconds investigating an unclear validation failure or weak platform
message. Use another available test/build control, command, manual/sample flow, or
static check; state what the platform did not reveal and continue. Never violate tool
or tab rules.

### Time recovery

- After 60-90 seconds without new evidence, stop editing and use the cheapest
   available discriminating check.
- After two failed AI attempts, switch to manual work for that checkpoint.
- At minute 26, reorder remaining independent work by acceptance value per minute.
- At minute 30, drop optional comments, cleanup, and abstractions.
- At minute 34, freeze features and enter integration.
- After minute 34, make only must-have correctness or build fixes.

## Integration and Ownership Audit (34:00-43:00)

Run the broadest available suite, typecheck, or build. Do not rerun only the latest
failing test. Repair root causes with the smallest patch.

Then inspect the final changed regions for:

- accidental deletions or unrequested files;
- weakened, skipped, or overfit tests;
- hardcoded values and fixture-specific logic;
- swallowed errors or broad exception handling;
- unsafe casts, `any`, ignored return values, or unchecked nulls;
- API and serialization drift;
- mutation, nondeterminism, and state leakage;
- unbounded memory, work, retries, goroutines, or queues;
- dead code and unnecessary abstractions; and
- stale assumptions from earlier checkpoints.

State final time and space complexity, including average-case behavior when it
differs materially from the worst case.

## Language Safety Scan

Always prefer repository-provided scripts. Use these as review prompts, not as a
reason to install tooling during the interview.

### Java

- Target Maven or Gradle tests before running the full suite.
- Check nullability, integer overflow, mutability, and collection ordering.
- Verify `equals` and `hashCode` contracts when objects become keys.
- Avoid broad exception handling and lost interrupt status.
- Check shared mutable state and synchronization when concurrency is present.

### TypeScript and Node.js

- Use package scripts and the configured test runner.
- Run the existing typecheck; use `tsc --noEmit` only when compatible with the repo.
- Reject `any`, unsafe assertions, or disabled checks used to hide errors.
- Check awaited promises, rejection propagation, event-loop blocking, and cleanup.
- Verify module format, runtime validation, object mutation, and deterministic order.

### Go

- Run a targeted `go test`, then `go test ./...` when time permits.
- Use `-race` only when supported and affordable.
- Check nil values, zero values, slice/map aliasing, and ignored errors.
- Check context cancellation, goroutine exits, channel ownership, and cleanup.
- Verify deterministic output where map iteration could leak into behavior.

## Evidence-Based Close (43:00-45:00)

Use this structure:

> I completed T1 through T4. Each checkpoint passed its focused check, and the final
> build, typecheck, and regression suite passed. The controlling operation is O(n)
> time and O(k) additional space. I rejected the generated cache abstraction because
> it changed invalidation behavior without helping the requirement; I retained its
> bounded test table after reviewing the cases. The remaining risk is platform-only
> timeout behavior, which I could not measure here, but the algorithm removes the
> prior quadratic path.

Never describe planned polish as completed work. If something remains incomplete,
name its exact status, impact, and smallest next step.

## Distinctive Senior Signal

The most memorable positive signal is not clever prompting. It is disciplined
prediction and traceability:

1. state what should happen before running a check;
2. connect every requirement to an invariant and test;
3. detect when an AI or human suggestion conflicts with evidence;
4. change direction without defensiveness; and
5. finish the full task rather than polishing an early checkpoint.

This demonstrates that the candidate can use AI as leverage while remaining the
technical owner.

## Preparation Program

Practice these scenarios under a strict 45-minute timer:

1. Add a feature to an unfamiliar multi-file repository.
2. Repair a subtle bug with a misleading AI diagnosis.
3. Optimize a correct but slow path and prove the improvement.
4. Extend an earlier task without regressing its contract.
5. Complete a mixed five-checkpoint chain with one independent task.

Rotate Java, TypeScript/Node, and Go. In each adversarial mock inject:

- one plausible but incorrect guide claim about the main code, call path, or command;
- one plausible but incorrect AI patch;
- one oversized or architecture-changing AI response;
- one interviewer suggestion that conflicts with a requirement; and
- one misleading platform error or hidden edge case.

The readiness gate is three consecutive mocks with:

- all required checkpoints complete;
- coding started by minute 9;
- broad validation started by minute 34-36;
- no unexplained or unvalidated generated code;
- focused and regression checks completed; and
- at least 4/5 in every primary observable area.

Use [the orientation prompt index](../template/codebase-orientation/README.md) for
repository research, [the live card](../template/ai-interview-live-card.md) during
practice, and [the mock scorecard](../template/ai-interview-mock-scorecard.md) for
evaluation.


