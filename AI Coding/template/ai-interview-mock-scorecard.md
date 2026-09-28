# AI-Assisted Interview Mock Scorecard

Use this template to create and score a 45-minute Senior SWE repository exercise.
Do not disclose the adversarial injections to the candidate before the mock.

## Scenario Setup

| Field | Value |
|---|---|
| Repository and language |  |
| Candidate |  |
| Date |  |
| Evaluator |  |
| Task count (2-5) |  |
| Dependency shape | Chain / fan-out / independent / mixed |
| Checkpoint release style | All visible / progressive |
| Checkpoint context style | Explicit task / implicit evidence / mixed |
| Pre-existing `git status --short` changes | None / list files and interviewer guidance |
| Research folder | `.interview/research/` |
| Task scratchpad folder | `.interview/tasks/` or root fallback |
| Prompt input method | Unchanged full prompts / same-file quick prompts |
| Mode sequence used | Agent research -> Agent task prep -> Human direction -> Plan -> Plan persistence -> Agent implementation -> Agent integration |
| Focused validation method | Command / platform button / manual flow / sample / diagnostic / static evidence |
| Broad validation method | Command / platform button / manual flow / available alternative |

Use the [orientation prompt index](codebase-orientation/README.md) during the mock.
Score its output as untrusted research, not as ground truth.

## Research and Plan Evidence

| Stage | Mode | Output | Line cap | Within cap? | Candidate verified it? |
|---|---|---|---|---|---|
| Architecture, flows, tests, class/method comment audit | Agent research | `.interview/research/00-architecture-tests-and-comments.md` | 180 |  |  |
| Bugs, unfinished work, gaps, risks | Agent research | `.interview/research/01-bugs-gaps-and-risks.md` | 100 |  |  |
| Verification and synthesis | Agent research | `.interview/research/02-orientation-summary.md` | 100 |  |  |
| Current task preparation | Agent | `.interview/tasks/task_<id>.md`: known values plus Agent Context | Template-specific |  |  |
| Given-checkpoint implementation plan | Plan | Chat-only sliced plan | Type-specific |  |  |
| Complete accepted-plan persistence | Manual or Agent persist-only | Same `.interview/tasks/task_<id>.md`: complete Accepted Plan | Before coding |  |  |
| Latest result | Agent implementation | Same `.interview/tasks/task_<id>.md`: Latest Snapshot | Task lifetime |  |  |

Agent research write-scope audit: only `.interview/research/*.md` changed: ___

Pass 1 comment audit: existing comments on all critical or large classes/methods classified
`ADEQUATE / NEEDS_ENHANCEMENT / MISSING`; proposals stayed in research: ___

## Task-Specific Plan Evidence

| Type | Max lines | Slice guidance | Plan passed? |
|---|---|---|---|
| Bug fix | 60 | One slice normally; optional second when boundaries require it |  |
| Feature | 90 | One slice if small; optional 2-5 vertical slices |  |
| Optimization | 80 | One experiment if sufficient; optional 2-4 one-variable experiments |  |
| Enhancement/refactor | 75 | One slice if small; optional 2-4 runnable boundary slices |  |

Complete persisted plan: ___  Persisted slice IDs in order: ___  Selected first slice ID: ___

## Checkpoint Context and Control Evidence

| Control | Required evidence | Pass? |
|---|---|---|
| Task-file seed | Correct type template; known values retained; every unfilled value marked TO BE FILLED BY AGENT |  |
| Clear-task default | Table-free note seeded in under 30 seconds; missing values marked TO BE FILLED BY AGENT; no discovery/subagents |  |
| Explicit context | Verbatim task plus expected, actual/missing, acceptance, constraints, non-goals, evidence, unknowns |  |
| Rare unclear-task discovery | Used only when task/acceptance was unclear; available observation discriminated alternatives |  |
| Optional Behavior Trace | For unclear task only: signal -> expected source -> entry -> relevant path -> exact gap, with evidence |  |
| Ambiguity | Plan asks concise questions one at a time; candidate answers; answers are stored with the complete plan during persistence |  |
| Invariants | 1-3 task-relevant invariants, each with evidence and a preserving/equivalence test |  |
| Human direction first | Before Plan mode, candidate states acceptance, simplest approach/part order, and predicted first check |  |
| Complete Plan response | Plan returns all slices at once in execution order, not one slice per turn |  |
| Slice shape | Each slice has an ordered ID/title plus only a bounded `Change` and proving `Check` |  |
| Plan self-check | AI rewrote invalid output; the final line of the entire Plan response is `Plan self-check: PASS` |  |
| Candidate Plan review | Before accepting, candidate compares AI with the human direction, requires evidence for deviations, and rejects unnecessary architecture |  |
| Complete-plan persistence | Before source/test edits, final Plan response is stored without summarizing; every slice appears exactly once and in order with plan-wide rules |  |
| Persistence method | Candidate chooses exactly one: AI copy by default, or manual copy when faster/unavoidable; AI edits only the task file, implements nothing, and stops |  |
| Persistence verification | Candidate checks complete plan, slice order, `Change`/`Check`, rules, final self-check, and no source/test/config/build changes |  |
| Replan persistence | Complete revised plan replaces Accepted Plan and passes the gate again before another slice |  |
| Single-file snapshot | Latest context, Accepted Plan, and Latest Snapshot maintained in the same task file; prior versions not accumulated |  |
| Slice selection | Candidate explicitly names one slice ID per Agent turn; Agent executes only it |  |
| Visible AI control | Candidate states intent before each prompt, reads generated changes, reviews them aloud, and explicitly accepts/revises/rejects |  |
| Parent-managed parallelism | Only for rare unclear/review cases: one parent prompt internally spawns at most two read-only workers and remains sole writer |  |
| Test discipline | After every code/test change, all exposed tests run before another edit; hidden/unavailable limits recorded |  |

## Checkpoint Design

Each checkpoint must have independently observable acceptance criteria. Later tasks
may extend earlier behavior, but they must not rely on an unstated requirement.

| ID | Type | Requirement delta | Depends on | Slice IDs | Acceptance test | Budget |
|---|---|---|---|---|---|---|
| T1 | Bug / Feature / Perf / Enhancement |  | None |  |  |  |
| T2 |  |  |  |  |  |  |
| T3 |  |  |  |  |  |  |
| T4 |  |  |  |  |  |  |
| T5 |  |  |  |  |  |  |

### Slice Execution Evidence

The evaluator records this table. The candidate does not maintain it during the
interview; the Agent-maintained Latest Snapshot is the candidate's progress record.

| Slice | Part/flow | Change | Check | Full exposed suite | Result |
|---|---|---|---|---|---|
|  |  |  |  |  | `COMPLETED / BLOCKED` |

Budget choices:

- 2 checkpoints: `13 / 12`
- 3 checkpoints: `9 / 8 / 8`
- 4 checkpoints: `7 / 6 / 6 / 6`
- 5 checkpoints: `5 / 5 / 5 / 5 / 5`

All budgets total 25 implementation minutes. Reserve minutes 0-9 for starting
conditions, full-codebase research, and task focus; 34-40 for integration; 40-43 for review; and 43-45 for
the close.

## Adversarial Injections

Include at least one injection from each selected category. An injection should test
judgment, not make completion impossible.

| Category | Planned injection | Trigger time/task | Expected strong response | Observed response |
|---|---|---|---|---|
| AI architecture | Hallucinated component or unsupported relationship | Research pass 1 | Candidate rejects claim without a valid file hyperlink |  |
| AI comments | Edits source comments during research or proposes trivial narration | Research pass 1 | Candidate restores files and keeps proposals only in research |  |
| AI tests | Test name implies coverage assertions do not provide | Research pass 1 | Candidate checks assertions and corrects the artifact |  |
| AI bug claim | Inference presented as an observed bug | Research pass 2 | Candidate downgrades it to risk/unknown |  |
| AI synthesis | Broken link or Mermaid node without grounding | Research pass 3 | Candidate repairs it before passing the gate |  |
| AI correctness | Plausible patch with a subtle boundary or state bug |  | Inspect, predict, test, reject/fix |  |
| AI scope | Unrequested abstraction or broad rewrite |  | Return to bounded requirement |  |
| AI overdesign | New hierarchy/nested classes when an existing helper or direct conditional is enough | Plan/implementation | Candidate keeps the simpler repository-consistent design |  |
| AI spiral | After uncertainty, AI proposes repeated rewrites/restructuring/start-over plans | Debugging | Candidate stops prompting, reduces the case, runs one discriminating check, and continues manually |  |
| Nerfed AI | AI gives only hints, cryptic/incomplete responses, or refusals | Any AI turn | Candidate uses it only for reviewable boilerplate/syntax/scaffolding and owns hard reasoning/code |  |
| Human pushback | Suggestion conflicting with an explicit invariant |  | Test with counterexample; disagree calmly |  |
| Task drift | AI searches beyond the explicit task or supplied implicit signal | Context/Plan | Candidate returns to the verified context and rejects unrelated work |  |
| Unnecessary discovery | Clear task, but AI tries to rediscover it or spawn workers | Task preparation | Candidate uses COMPLETE CURRENT TASK and proceeds to Plan |  |
| Implicit checkpoint | Several plausible tasks behind one signal | Rare discovery | Candidate uses available observation, discriminates, and confirms scope when ambiguous |  |
| Fabricated trace | AI jumps from signal to a guessed file | Rare discovery | Candidate requires Signal -> Expected source -> Entry -> Relevant path -> Gap, all with evidence |  |
| False invariant | AI calls an implementation detail a required invariant | Plan mode | Candidate demands requirement/test/API evidence and removes it |  |
| Split scratchpad | AI creates separate context and plan files | Preparation/implementation | Candidate keeps current context, Accepted Plan, and Latest Snapshot in task_<id>.md |  |
| Partial plan copy | AI stores only the selected slice or summarizes the plan | Persistence | Candidate requires every accepted slice exactly once/in order with all fields and plan-wide rules |  |
| Premature implementation | AI edits project files while copying the plan | Persistence | Candidate rejects the turn, restores the boundary, verifies persistence, then starts a separate implementation turn |  |
| Stale snapshot | AI appends history instead of replacing current state | Persistence/implementation | Candidate replaces Accepted Plan only during persistence and Latest Snapshot only during implementation |  |
| Manual subagent orchestration | AI tells candidate to launch or coordinate workers | Rare discovery | Candidate sends one parent prompt; parent handles spawning/reconciliation internally |  |
| Excessive delegation | Parent tries to spawn more than two workers | Rare discovery | Candidate caps delegation at two independent read-only roles |  |
| Parallel writers | AI proposes multiple agents editing related files/slices | Agent implementation | Candidate uses one writer and limits helpers to read-only evidence |  |
| One-shot feature | AI tries to implement all feature slices together | Agent implementation | Candidate names one slice ID and limits the turn to it |  |
| Skipped full suite | AI runs only the focused test after a change | Agent implementation | Candidate runs every exposed test before the next edit |  |
| Unmeasured optimization | AI claims improvement without baseline/comparison | Optimization slice | Candidate rejects it and measures before continuing |  |
| Hidden tests | Missing visible boundary/ordering/failure case |  | Enumerate and test equivalence classes |  |
| Platform | No shell command/filter or only Run Tests/Build/manual controls |  | Use the cheapest available observation; record NOT_AVAILABLE when no pre-check exists |  |

Do not penalize the candidate for rejecting an incorrect hint. Score whether the
candidate uses evidence, communicates professionally, and adapts when the contract
actually changes.

## Timeline Evidence

| Gate | Target | Actual | Pass? | Notes |
|---|---|---|---|---|
| Starting conditions confirmed | 0:30 |  |  |  |
| Architecture/flows/tests/comments artifact complete | 4:15 |  |  |  |
| Bugs/gaps/risks artifact complete | 5:30 |  |  |  |
| Orientation summary and grounding gate complete | 7:00 |  |  |  |
| Checkpoint context verified/confirmed | 8:00 |  |  |  |
| Given-checkpoint plan accepted | 8:45 |  |  |  |
| Complete Accepted Plan persisted and verified; first slice selected | 9:00 |  |  |  |
| Coding started | 9:15 |  |  |  |
| First checkpoint complete | 19:00 or earlier |  |  |  |
| Half of checkpoints complete | 26:00 |  |  |  |
| Required implementation complete | 34:00 |  |  |  |
| Broad validation started | 34:00-36:00 |  |  |  |
| Ownership review started | 40:00 |  |  |  |
| Evidence close started | 43:00 |  |  |  |

## Primary Rubric

Score each area independently from 1 to 5.

### 1. Problem Solving: ___ / 5

| Signal | Observed evidence |
|---|---|
| Completed full-codebase orientation before classifying the task |  |
| Established explicit context or inferred the implicit task from the best available observation |  |
| Formed a provisional approach and predicted check before asking AI to plan |  |
| Asked at most three material questions; stated cheap reversible assumptions |  |
| Identified evidenced invariants, preserving tests, edge cases, and dependencies |  |
| Selected a coherent order and realistic tradeoff |  |
| Adjusted the plan when evidence changed |  |

### 2. Code Development and Understanding: ___ / 5

| Signal | Observed evidence |
|---|---|
| Used architecture, flow, quality, and test research to locate the change |  |
| Made minimal, complete, integrated changes |  |
| Preserved APIs and previous checkpoint behavior |  |
| Read every generated change and explained all retained existing and generated code |  |
| Named one slice; Agent edited/tested/updated snapshot; candidate reviewed evidence |  |

### 3. Verification and Debugging: ___ / 5

| Signal | Observed evidence |
|---|---|
| Predicted results before execution |  |
| Used focused checks to discriminate hypotheses |  |
| Covered boundaries, errors, and hidden-test classes |  |
| Ran every exposed test after every code/test change before another edit |  |
| Diagnosed causes rather than symptoms |  |

### 4. Technical Communication: ___ / 5

| Signal | Observed evidence |
|---|---|
| Stated intent before every AI prompt |  |
| Reviewed AI output aloud and communicated decisions/test results concisely |  |
| Explained evidence and reasoning before pivots; handled pushback professionally |  |
| Closed with completion, evidence, complexity, and risk |  |

## Cross-Cutting Rubric

### 5. CS Fundamentals: ___ / 5

- Correctness reasoning:
- Data structure and algorithm choice:
- Time and space complexity:
- Boundary or concurrency reasoning:

### 6. AI Fluency: ___ / 5

- Formed and stated a human plan before requesting an AI plan:
- Kept architecture/strategy human-owned and preferred the simplest repository pattern:
- Stated intent before each prompt and reviewed generated output aloud afterward:
- Issued the three repository research prompts sequentially rather than all at once:
- Sent fixed prompts unchanged or used same-file quick prompts without rebuilding them:
- Persisted each research pass to the required Markdown file:
- Kept artifacts within line budgets and removed repetition/filler:
- Kept Agent research writes inside `.interview/research/`:
- Audited existing comments on every critical or large class/method without editing source:
- Switched to Plan mode, received all slices in one response, and reviewed it before accepting:
- Explicit/implicit checkpoint anchoring: verbatim explicit context or implicit
  discovery bounded to the supplied signal; no arbitrary repository task search:
- Clear-task efficiency: used COMPLETE CURRENT TASK without discovery or subagents:
- Ambiguity confirmation: observed/traced the implicit signal and confirmed scope
  instead of guessing when evidence remained ambiguous:
- Single task-file lifecycle: created the correct `task_<id>.md`, passed CURRENT_TASK,
  and kept current context/Accepted Plan/Latest Snapshot together:
- Rare Behavior Trace: only when unclear, verified signal, expected source, entry,
  relevant path, and exact gap against file/symbol evidence:
- Asked concise conversational questions when context was missing/ambiguous and
  persisted answers with the accepted plan before implementation:
- Chose exactly one persistence method: AI copy by default or manual copy when needed;
  stored every slice exactly once/in order and made no project-file edits:
- Verified Accepted Plan before source edits and Latest Snapshot after validation:
- Returned to Agent mode only for approved implementation and integration:
- Selected the correct task-specific Plan prompt and decomposition:
- Named one slice ID per Agent turn; Agent implemented only it and stopped:
- Parent-managed parallelism: sent one parent prompt; it internally spawned at most
  two read-only workers, reconciled results, and remained the only writer:
- Platform-neutral observation: used buttons/manual samples/diagnostics/static
  evidence when commands were absent and recorded NOT_AVAILABLE when no pre-check existed:
- Ran all exposed tests after every code/test change before another edit:
- Returned to Plan mode when evidence invalidated unfinished slices:
- Grounded every factual code claim with a verified Markdown file hyperlink:
- Used required architecture diagrams and added optional diagrams only when useful:
- Grounded every code component in each diagram that was included:
- Corrected contradictions and unsupported assumptions before task focus:
- Bounded, contextual delegation:
- Critical review of generated output:
- Drift or hallucination detected:
- Switched to direct coding when further prompting was slower:
- Interrupted an AI spiral instead of following rewrites/restructuring:
- Used nerfed AI only for reviewable boilerplate/syntax/scaffolding:

### 7. Judgment and Ownership: ___ / 5

- Tradeoff quality:
- Evidence-based accept/reject decisions:
- Scope and compatibility discipline:
- Accountability for final code:

### 8. Completion and Time: ___ / 5

- Required checkpoints complete:
- Focused and broad validation complete:
- Final task snapshot, diff, full-suite result, complexity, and risk reviewed:
- Candidate gave a concise spoken task closeout before the next checkpoint:
- Hard gates respected:
- Optional polish dropped when needed:

## Score Definitions

| Score | Meaning |
|---|---|
| 5 | Independent, correct, proactive, evidence-driven; catches adversarial signals and finishes cleanly |
| 4 | Strong result with one minor miss or quickly repaired defect; clear ownership |
| 3 | Functional core but meaningful guidance, verification, communication, or completion gaps |
| 2 | Multiple incomplete tasks, weak understanding, or repeated reliance on unverified output |
| 1 | Cannot establish an approach or produce defensible working code |

An overall average can hide a fatal weakness. A mock is not interview-ready if any
primary area is below 4, required checkpoints are incomplete, broad validation is
skipped, or retained AI code cannot be explained.

## Requirement Traceability

| Checkpoint | Requirement satisfied? | Focused evidence | Regression evidence | Candidate explanation |
|---|---|---|---|---|
| T1 |  |  |  |  |
| T2 |  |  |  |  |
| T3 |  |  |  |  |
| T4 |  |  |  |  |
| T5 |  |  |  |  |

## Failure Pattern Log

Mark observed patterns:

- [ ] Spent time asking about capabilities that are always available
- [ ] Focused on the checkpoint before completing full-codebase orientation
- [ ] Combined all repository research into one oversized prompt
- [ ] Spent time editing or reconstructing a prompt during the interview
- [ ] Left research only in chat instead of persisting Markdown artifacts
- [ ] Accepted an oversized, repetitive, prose-heavy, or generic research artifact
- [ ] Omitted a first-party module or primary flow from the architecture artifact
- [ ] Allowed Agent research to modify any project file, including source comments
- [ ] Proposed narration for trivial methods or failed to recognize an adequate comment
- [ ] Asked AI to discover, rename, or reframe the checkpoint instead of solving it
- [ ] Allowed AI to search for arbitrary repository work beyond the explicit task or supplied implicit signal
- [ ] Guessed checkpoint scope while evidence was ambiguous instead of confirming it
- [ ] Seeded a task file with missing task/signal/acceptance/constraints/evidence/unknown fields instead of UNKNOWN
- [ ] Split one checkpoint across separate context, plan, and work files
- [ ] Guessed an implicit checkpoint without an available observation and grounded Behavior Trace
- [ ] Ran discovery or spawned workers even though the task and acceptance were clear
- [ ] Entered Plan mode without `CURRENT_TASK` or ignored unresolved context
- [ ] AI returned a sentinel instead of asking a concise conversational question
- [ ] Asked an answerable, non-material, or cheaply reversible clarification question
- [ ] Claimed an invariant without requirement, test, API/schema, state-rule, or equivalence evidence
- [ ] Planned in Agent mode instead of switching to Plan mode
- [ ] Asked AI to plan before forming and stating a provisional human approach
- [ ] Prompted without stating intent, or reviewed output silently/only after the fact
- [ ] Entered implementation before reviewing and accepting the plan
- [ ] Treated Plan mode as one-slice-at-a-time instead of receiving the complete ordered plan
- [ ] Edited source/tests before the complete Accepted Plan and every slice were persisted and verified
- [ ] Persisted only the selected slice or a summary instead of the complete final Plan response
- [ ] Performed both AI and manual persistence instead of choosing one method
- [ ] Combined AI plan persistence and implementation in one turn
- [ ] Allowed the AI persist-only turn to edit source, tests, configuration, or build files
- [ ] Replanned but did not persist and verify the complete revised plan before continuing
- [ ] Accumulated history instead of replacing Accepted Plan during persistence and Latest Snapshot during implementation
- [ ] Started Agent implementation without naming one slice ID
- [ ] Tried to launch/coordinate subagents directly instead of prompting the parent Agent once
- [ ] Parent spawned more than two read-only workers for checkpoint grounding or review
- [ ] Used parallel writers or overlapping/dependent subagent assignments
- [ ] Failed to reconcile read-only subagent evidence in the parent Agent
- [ ] Ignored the platform-neutral ladder: existing output, button, manual/sample flow, diagnostic, static evidence, or NOT_AVAILABLE
- [ ] Required a shell command when a platform button/manual/sample/static check was the available evidence
- [ ] Invented a pre-change result instead of recording NOT_AVAILABLE
- [ ] Accepted a vague or oversized slice without a bounded `Change` and proving `Check`
- [ ] Accepted an unnecessary hierarchy, nested class design, or abstraction over a simple existing pattern
- [ ] Implemented multiple slices in one Agent turn
- [ ] Made another code/test change before running every exposed test
- [ ] Continued after a blocked slice or failing tests
- [ ] Claimed optimization success without before/after measurement
- [ ] Improvised around an invalid plan instead of replanning unfinished slices
- [ ] Accepted a factual code claim without a Markdown hyperlink to an actual file
- [ ] Accepted a broken or directory-only grounding link
- [ ] Accepted a Mermaid code component without a Diagram grounding link
- [ ] Required a diagram in a test, bug, or checkpoint artifact when it added no clarity
- [ ] Treated an inference or suspicion as an observed bug
- [ ] Claimed test coverage from filenames without reading assertions
- [ ] Proceeded despite failed orientation-gate checks
- [ ] Asked irrelevant boilerplate questions for the checkpoint type
- [ ] Rebuilt all orientation artifacts for a progressive checkpoint without new evidence
- [ ] Followed AI into an architectural decision
- [ ] Accepted generated code without full review
- [ ] Built on unvalidated output
- [ ] Followed an AI spiral into rewrites/restructuring instead of reducing the case and checking evidence
- [ ] Kept re-prompting nerfed AI for hard reasoning instead of coding directly
- [ ] Patched symptoms instead of testing a root-cause hypothesis
- [ ] Weakened types, errors, or tests to obtain green output
- [ ] Failed to rerun earlier checkpoints
- [ ] Followed interviewer authority despite conflicting evidence
- [ ] Argued after evidence disproved the candidate's position
- [ ] Spent too long fighting the platform
- [ ] Narrated keystrokes or stayed silent through decisions
- [ ] Polished early work while later checkpoints remained incomplete
- [ ] Claimed performance improvement without a baseline
- [ ] Could not explain final complexity or retained generated code

## Distinctive Positive Signal

What will the interviewer remember positively about this candidate?

> _Record one concrete incident._

Look for a concrete incident, such as catching a plausible architecture claim with a
broken file link, correcting a Mermaid flow from source evidence, predicting a
failure before running it, defending an
invariant with a counterexample, or simplifying an overbuilt suggestion while still
completing every checkpoint.

## Final Assessment

| Field | Result |
|---|---|
| Primary scores | PS: __ / CD: __ / VD: __ / TC: __ |
| Cross-cutting scores | CS: __ / AI: __ / JO: __ / CT: __ |
| Required checkpoints completed | __ / __ |
| Focused checks passed | __ / __ |
| Broad validation | Pass / Fail / Not run |
| Overall recommendation | Strong Hire / Hire / Lean Hire / Borderline / No Hire |

### Strengths

1. _
2. _
3. _

### Highest-Leverage Improvements

1. _
2. _
3. _

### Next Mock Injection

> _Describe the next injected failure or misleading signal._

## Readiness Tracker

The candidate is ready after three consecutive qualifying mocks.

| Mock | Date | All tasks complete | Primary areas >= 4 | Orientation gate passed | Broad check run | No unexplained AI code | Qualifies |
|---|---|---|---|---|---|---|---|
| 1 |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |
