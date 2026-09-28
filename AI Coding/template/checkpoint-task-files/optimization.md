# Task <ID>: <Optimization Title>

- Type: OPTIMIZATION
- Status: DRAFT
- Task: <fill or TO BE FILLED BY AGENT>
- Workload/metric/target: <fill or TO BE FILLED BY AGENT>
- Unknowns: TO BE FILLED BY AGENT

## Acceptance

- Correctness remains unchanged for the same inputs.
- The agreed metric improves against the same representative workload.
- Before/after evidence supports the result when measurement is available.
- All previously passing tests still pass.
- Task-specific threshold: TO BE FILLED BY AGENT

## Constraints

- After every code or test change, run all exposed/available tests before another change.
- If tests are hidden/unavailable, run every exposed test and record the limitation.
- Do not change observable output, errors, ordering, mutation, or side effects.
- Do not change, remove, or weaken correctness tests.
- Measure one major change at a time against a comparable workload.
- Follow existing repository style and avoid unrelated rewrites.
- Additional constraints/non-goals: TO BE FILLED BY AGENT

## Agent Context

- Baseline/measurement method: TO BE FILLED BY AGENT
- Relevant code/bottleneck: TO BE FILLED BY AGENT
- Optimization hypothesis: TO BE FILLED BY AGENT
- Correctness/performance validation: TO BE FILLED BY AGENT
- Evidence: TO BE FILLED BY AGENT
- Behavior trace, only if task is unclear: TO BE FILLED BY AGENT

## Invariants

- Outputs, errors, ordering, mutation, and side effects remain equivalent.
- All previously passing correctness tests remain passing.
- Additional task-specific invariant: TO BE FILLED BY AGENT

## Accepted Plan

- Persistence gate: Before any source/test edit, replace the placeholder with the
  complete final Plan response. Preserve every slice exactly once and in order with
  `Change` and `Check`, plus plan-wide validation and the final
  `Plan self-check: PASS` line; never store only the selected slice or a summary.
- Complete accepted plan: TO BE FILLED BY AGENT

## Latest Snapshot

- Status: NOT_STARTED
- Change and before/after result: TO BE FILLED BY AGENT
- Files changed: NONE
- Validation/result: NOT_RUN
- Remaining: TO BE FILLED BY AGENT
- Risk/complexity: TO BE FILLED BY AGENT