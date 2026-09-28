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

No public framework can guarantee coverage of undisclosed company scorecards. This
framework maps every criterion found in the local preparation material and verified
public guidance to observable interview behavior.

## Success Definition

By minute 45, the candidate should have:

- completed every required checkpoint;
- preserved behavior from earlier checkpoints;
- run focused validation after each meaningful change;
- run the broadest available regression check;
- explained correctness, complexity, tradeoffs, and residual risk;
- reviewed and understood every retained AI-generated change; and
- made one memorable senior-level signal: a visible chain from each requirement to
  an invariant, implementation decision, and test result.

## Rubric Contract

### Primary observable areas


| Evaluation area                    | What the interviewer must observe                                                                                                        | Required evidence                                                  |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| Problem Solving                    | Clarifies acceptance criteria, identifies invariants and edge cases, orders dependencies, compares realistic approaches                  | Checkpoint ledger and explicit implementation order                |
| Code Development and Understanding | Finds the owning path, follows local patterns, preserves contracts, makes minimal coherent changes, explains existing and generated code | Integrated working code with no unexplained region                 |
| Verification and Debugging         | Predicts behavior, reproduces failures, runs focused checks, diagnoses causes, and reruns regressions                                    | One focused check per checkpoint and a final broad check           |
| Technical Communication            | States intent before acting, reports decisions and results, incorporates feedback, and explains pivots                                   | Concise updates at decision boundaries and an evidence-based close |

### Cross-cutting areas


| Evaluation area        | What the interviewer must observe                                                                                 | Required evidence                                                                   |
| ---------------------- | ----------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| CS Fundamentals        | Correctness reasoning, suitable data structures, complexity, boundaries, and concurrency reasoning where relevant | Correctness argument and final time/space complexity                                |
| AI Fluency             | Bounded delegation, useful context, critical review, drift detection, and manual fallback                         | No AI change accepted without inspection and validation                             |
| Judgment and Ownership | Explicit tradeoffs, evidence-based disagreement, minimal scope, and responsibility for all code                   | Every accept, reject, or pivot tied to a requirement, invariant, code fact, or test |
| Completion and Time    | Hard time gates, fast checkpoint handoff, and deliberate scope control                                            | All required implementation complete by minute 34                                   |

Passing tests alone do not satisfy the rubric. The candidate must make the reasoning
and verification process observable.

## The Evidence Ledger

Create this ledger in the editor or scratchpad before implementation. Populate it
from the task statement and the verified orientation map:


| ID | Type | Requirement delta | Dependency | Invariant or risk | Owning code | Acceptance check | Status        |
| -- | ---- | ----------------- | ---------- | ----------------- | ----------- | ---------------- | ------------- |
| T1 |      |                   | None       |                   |             |                  | TODO          |
| T2 |      |                   | T1 / None  |                   |             |                  | LOCKED / TODO |
| T3 |      |                   |            |                   |             |                  | LOCKED / TODO |

Allowed statuses are `LOCKED`, `TODO`, `DOING`, `GREEN`, and `REGRESSED`.

For all-visible tasks, topologically order dependent checkpoints. Among independent
tasks, address the highest uncertainty while time reserve is healthy, then finish
shorter tasks. For progressively revealed tasks, design only for the current
contract. Do not build speculative extension points for unknown follow-ups.

## 45-Minute State Machine


| Time        | State             | Required outcome                                                  | Exit gate                                             |
| ----------- | ----------------- | ----------------------------------------------------------------- | ----------------------------------------------------- |
| 0:00-0:30   | Environment delta | Pre-shared capability profile loaded; only changes confirmed      | Execution mode and release mode selected              |
| 0:30-5:00   | AI orientation    | Task-scoped`ORIENTATION_MAP` generated and three anchors verified | Owner, flow edge, and focused command are trustworthy |
| 5:00-8:00   | Plan              | Ledger, order, approach, risk, and focused check selected         | Coding starts no later than 8:00                      |
| 8:00-34:00  | Checkpoints       | Every required task implemented and narrowly validated            | All required rows are`GREEN`                          |
| 34:00-40:00 | Integrate         | Broad suite/typecheck/build is green; regressions repaired        | Integrated behavior is validated                      |
| 40:00-43:00 | Own               | Final changed regions and complexity reviewed                     | Candidate can defend every retained change            |
| 43:00-45:00 | Close             | Results, tradeoffs, AI judgment, and risk summarized              | Interviewer has explicit evidence for each rubric     |

### Checkpoint budgets

Each checkpoint budget includes implementation, review, and focused validation.


| Number of checkpoints | Budgets from minute 8 to minute 34 | Total      |
| --------------------- | ---------------------------------- | ---------- |
| 2                     | 13 + 13 minutes                    | 26 minutes |
| 3                     | 10 + 8 + 8 minutes                 | 26 minutes |
| 4                     | 8 + 6 + 6 + 6 minutes              | 26 minutes |
| 5                     | 6 + 5 + 5 + 5 + 5 minutes          | 26 minutes |

Reallocate only when an early checkpoint is genuinely foundational. Keep these hard
gates:

- first green checkpoint around minute 18 or earlier;
- at least half of the checkpoints green by minute 26;
- all required implementation green by minute 34;
- no optional polish after minute 30; and
- no new features after minute 34.

## Phase 1: Load the Known Environment (0:00-0:30)

The recruiter or practice environment normally exposes capabilities before the
interview. Record this profile during preparation rather than rediscovering it while
the clock is running:


| Capability                                    | Known baseline            | Prepared fallback                          |
| --------------------------------------------- | ------------------------- | ------------------------------------------ |
| Available model and switching policy          |                           | Stay on the default model                  |
| Repository and Git initialization             |                           | Track changed files manually               |
| AI file visibility and context limits         |                           | Supply bounded file/symbol context         |
| Search, read, edit, terminal, and tool calls  |                           | Read-only, chat-only, or manual mode       |
| Build, test, typecheck, and runtime feedback  |                           | Focused manual harness or code trace       |
| Internet, clipboard, and tab restrictions     | Hackerank : single AI tab | Use only the provided environment          |
| Chat history and scratch-artifact persistence | HOW to check?             | Keep a compact map in the current response |

Prepare four modes:

1. **Full agent:** AI can search/read/edit/run within the repository.
2. **Read-only assistant:** AI can search/read; the candidate edits and runs.
3. **Chat-only assistant:** the candidate supplies bounded snippets or file context.
4. **Manual fallback:** no dependable AI assistance is available.

At interview start, ask only:

1. Has any published capability or restriction changed?
2. Are checkpoints all visible or progressively revealed?
3. Is the starting repository state different from the supplied baseline? Ask this
   only when the state is ambiguous.

Do not re-ask whether model switching, Git, tool calls, file access, or external tabs
are available when those facts were already supplied. Select the prepared execution
mode and move on.

Suggested narration:

> I am using the published environment profile unless anything changed. I will have
> the assistant produce a read-only, task-scoped map, verify its owner, one flow edge,
> and its test command, then implement and validate one checkpoint at a time.

Do not spend interview time creating elaborate AI configuration or project
scaffolding unless the task explicitly requires it.

## Phase 2: AI-Assisted Task Orientation (0:30-5:00)

Read the current checkpoint before prompting. Then invoke the complete
[codebase-orientation prompt](../template/ai-codebase-orientation-prompt.md) using
the selected capability mode.

The assistant must perform read-only, task-scoped exploration and return an
`ORIENTATION_MAP` in chat or permitted scratch space. It must not edit source files
or begin implementation. The map must contain:

- a compact task interpretation and classification;
- task-relevant HLD components and external boundaries;
- LLD files, classes, interfaces, functions, and ownership;
- entry-to-exit control flow, data flow, error flow, state, and side effects;
- observed build, focused-test, and broad-regression commands;
- relevant tests and observable coverage gaps;
- the likely change surface and contracts that must remain stable;
- invariants, risks, and unresolved gaps; and
- three proposed verification anchors.

Every material claim must cite an exact file and symbol when available. The assistant
must distinguish `OBSERVED`, `INFERRED`, and `UNKNOWN` facts and attach confidence.
Commands may be called observed only when found in repository evidence.

### Three-anchor audit

Do not line-by-line reread the repository. Spend at most 30-45 seconds checking:

1. **Owner:** the claimed symbol actually controls or mutates the target behavior.
2. **Flow:** one important caller-to-owner or owner-to-dependency edge is real.
3. **Check:** the focused validation command exists and targets the relevant slice.

Correct the map when one anchor fails. If two anchors fail, discard it and fall back
one capability mode. An attractive diagram with weak evidence is not orientation.

### Clarification funnel

Do not ask a universal checklist. A possible question reaches the interviewer only
when all four conditions hold:

1. the task statement does not answer it;
2. code, tests, and the verified orientation map do not answer it;
3. the answer changes implementation or acceptance; and
4. a wrong assumption would cause meaningful rework or an incorrect result.

Ask at most two or three material questions. For a low-cost, reversible ambiguity,
state the assumption and continue.


| Task type                | Ask only when relevant and unresolved                                                                                    |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------ |
| Bug fix                  | Expected versus actual behavior; minimal reproducer; affected scope; compatibility expectations                          |
| Feature                  | Input/output/error contract; precedence or tie-breaking; state and side effects; ordering, idempotency, or compatibility |
| Performance optimization | Representative workload; bottleneck; target metric and threshold; measurement method; semantics to preserve              |
| Enhancement or refactor  | Observable behavior and API to preserve; migration allowance; intended extension axis; compatibility boundary            |

Activate security, concurrency, transaction, persistence, cancellation, or external
failure questions only when the task or code path touches those concerns. For
example, do not ask whether a performance target is asymptotic or measured during an
unrelated parsing bug fix.

For a progressive checkpoint, give the assistant the verified prior map and request
the delta form from the orientation prompt. It should report only new or invalidated
requirements, paths, flows, tests, assumptions, and risks rather than remapping the
repository.

Before coding, state:

- the one-line acceptance condition;
- one important invariant;
- one edge case;
- the likely owning path;
- the selected approach and one realistic alternative; and
- expected time and space complexity.

Do not enumerate artificial alternatives merely to appear thoughtful. Compare only
choices that could reasonably change the implementation.

## Phase 3: Execute Checkpoints (8:00-34:00)

Run the same loop for every task.

### The checkpoint loop

1. **Delta:** Restate what changed from the previous requirement. If the checkpoint
   crosses an unmapped boundary, request a delta orientation rather than a full scan.
2. **Predict:** Name the affected path and expected result of the focused check.
3. **Assign:** Decide whether manual work or bounded AI delegation is cheaper.
4. **Implement:** Make the smallest complete change that satisfies the checkpoint.
5. **Inspect:** Review requirement, API, type, error, complexity, and concurrency
   semantics in every changed region.
6. **Verify:** Run the cheapest check capable of disproving the current hypothesis.
7. **Report:** State the result, update the ledger, and request the next checkpoint.

Suggested handoff:

> T2 is green: the new error path is covered by the focused test, and the T1 tests
> still pass. The implementation remains linear. I am ready for the next checkpoint.

### Task exit contracts

#### Bug fix

1. Reproduce the failure or characterize it with a concrete input.
2. State one falsifiable root-cause hypothesis.
3. Choose the cheapest check that could disprove the hypothesis.
4. Add or identify a regression test.
5. Make the smallest root-cause repair.
6. Rerun the focused test and affected regressions.

Do not combine the fix with cleanup unless cleanup is necessary for correctness.

#### Feature

1. Define input, output, error, ordering, and compatibility contracts.
2. Identify the thinnest end-to-end path through the existing architecture.
3. Preserve public APIs unless the requirement explicitly changes them.
4. Cover the happy path, a boundary, and a failure path.
5. Confirm earlier checkpoints still pass.

#### Performance optimization

1. Establish current complexity or obtain a reproducible baseline.
2. Name the specific bottleneck and target.
3. State which semantics must remain unchanged.
4. Optimize the controlling path without unrelated rewrites.
5. Compare before and after using complexity or measurements.
6. Rerun correctness and regression tests.

Passing tests proves compatibility, not improved performance. The optimization needs
its own evidence.

#### Enhancement or refactor

1. Characterize current observable behavior.
2. Protect that behavior with existing or focused tests.
3. Change one ownership boundary at a time.
4. Avoid speculative abstractions for possible future checkpoints.
5. Run the broadest affordable regression check.

## AI Control Protocol

### Human-owned decisions

The candidate owns:

- requirement interpretation and acceptance criteria;
- architecture, algorithms, data structures, and invariants;
- tradeoffs and task ordering;
- whether a generated patch is retained; and
- final correctness and explanation.

Good AI assignments include bounded repository search, repetitive edits,
boilerplate, test enumeration, unfamiliar syntax, and ranked debugging hypotheses.
Do the work manually when it takes less than roughly one minute or when prompting
plus review would cost more.

### Six-field prompt envelope

Use this structure rather than pasting the raw problem:

```text
Target: <one method, test, or bounded behavior>
Context: <exact files, symbols, and current failure>
Requirement: <observable acceptance condition>
Constraints: <invariants, APIs, complexity, language/version>
Non-goals: <files/behavior not to change>
Output: <analysis, small patch, tests, or ranked hypotheses> plus validation command
```

Implementation example:

```text
Target: implement retry classification in RetryPolicy.shouldRetry.
Context: RetryPolicy.java and RetryPolicyTest.java; current callers expect a boolean.
Requirement: retry 429 and 5xx responses, but never retry other 4xx responses.
Constraints: preserve the public signature and O(1) behavior; no new dependency.
Non-goals: do not change backoff calculation or callers.
Output: propose the smallest patch and the focused tests. Do not edit existing tests.
```

Debugging example:

```text
Given this exact failure and the current implementation, return at most three ranked
root-cause hypotheses. For each, give the cheapest discriminating check. Do not
rewrite the implementation yet.
```

Review example:

```text
Review only the changed regions against these acceptance criteria. Identify API,
correctness, edge-case, type, error-handling, concurrency, and complexity risks.
Do not propose style-only refactors.
```

### Stop conditions

Stop using AI for the current slice after:

- two incorrect attempts;
- an unsolicited architectural rewrite;
- repeated requirement or API drift;
- deletion or weakening of tests;
- a false fix such as hardcoding, swallowed errors, or unsafe typing; or
- output too large to verify within the checkpoint budget.

Return to the invariant, create a minimal probe, and continue manually. Switching
models is rarely worth the context and review cost during a 45-minute round.

### Safe pipelining

While the assistant generates, explain the already selected approach, update the
ledger, or inspect a previously generated bounded change. Never build on unreviewed
output. Parallel activity should eliminate idle time, not create parallel branches
of unverified code.

## Adversarial and Unreliable Environment Protocol

### Unreliable coding assistant

Treat every response as an untrusted patch:

1. Compare changed scope with the ledger.
2. Inspect additions and deletions.
3. Check API, type, errors, complexity, security, and concurrency semantics.
4. Predict a check result.
5. Compile or test before building on the patch.

If the assistant begins proposing rewrites instead of explaining the failure, say:

> This changes more than the failing invariant requires. I am discarding it, reducing
> the case, and testing the controlling branch directly.

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

Spend at most 60 seconds fighting an unavailable capability. Use the known build or
manual fallback, state the limitation, and continue. Never violate tool or tab rules
to compensate for a restricted platform.

### Time recovery

- After 60-90 seconds without new evidence, stop editing and run the cheapest
  discriminating check.
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

- one plausible but incorrect orientation claim about an owner, flow, or command;
- one plausible but incorrect AI patch;
- one oversized or architecture-changing AI response;
- one interviewer suggestion that conflicts with a requirement; and
- one missing tool capability or hidden edge case.

The readiness gate is three consecutive mocks with:

- all required checkpoints complete;
- coding started by minute 8;
- broad validation started by minute 34-36;
- no unexplained or unvalidated generated code;
- focused and regression checks completed; and
- at least 4/5 in every primary observable area.

Use [the orientation prompt](../template/ai-codebase-orientation-prompt.md) to create
the map, [the live card](../template/ai-interview-live-card.md) during practice, and
[the mock scorecard](../template/ai-interview-mock-scorecard.md) for evaluation.

## Evidence and Scope

Local preparation sources:

- [Meta-style AI coding notes](../../company%20wise/metA/AICoding/details.md)
- [AI coding basics](../basics.md)
- [AI failure modes](../mistakes.md)
- [Structured AI workflow](structured/idea.md)
- [Senior system-coding rubric](../../prompts/interview_guidelines.md)
- [Tradeoff practice note](../../company%20wise/google/rubrics/rubrics.md)
- [45-minute timing failure report](../../company%20wise/airbnb/1p3a/38.md)

The Meta-style wording in the local notes is useful preparation material, but its
public provenance could not be verified. The Google and Airbnb files are practice
notes and candidate reports, not official company policy.

Verified public sources:

- [HackerRank: The New Technical Hiring Bar: CS Fundamentals, AI Fluency, and Judgment](https://www.hackerrank.com/blog/the-new-technical-hiring-bar-cs-fundamentals-ai-fluency-and-judgment/)
- [HackerRank: AI Interviewer vs. Human Interviewer](https://www.hackerrank.com/blog/ai-interviewer-vs-human-interviewer-strengths-trade-offs-and-when-to-use-each/)
- [HackerRank: The Future of Developer Hiring](https://www.hackerrank.com/lp/next-gen-hiring-wp/)
