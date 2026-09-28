# Task <ID>: <Bug Title>

- Type: BUG
- Status: DRAFT
- Task: <fill or TO BE FILLED BY AGENT>
- Expected: <fill or TO BE FILLED BY AGENT>
- Actual/signal: <fill or TO BE FILLED BY AGENT>
- Unknowns: TO BE FILLED BY AGENT

## Acceptance

- Failing test(s) or observed behavior now pass.
- A focused regression check covers the bug.
- All other previously passing tests still pass.
- Task-specific acceptance: TO BE FILLED BY AGENT

## Constraints

- After every code or test change, run all exposed/available tests before another change.
- If tests are hidden/unavailable, run every exposed test and record the limitation.
- Do not change, remove, or weaken tests merely to make the fix pass.
- Preserve existing public contracts and behavior outside the bug.
- Follow existing repository style and patterns.
- Avoid unrelated refactors.
- Additional constraints/non-goals: TO BE FILLED BY AGENT

## Agent Context

- Relevant code/path: TO BE FILLED BY AGENT
- Root cause: TO BE FILLED BY AGENT
- Evidence: TO BE FILLED BY AGENT
- Available validation: TO BE FILLED BY AGENT
- Behavior trace, only if task is unclear: TO BE FILLED BY AGENT

## Invariants

- All previously non-failing tests remain passing.
- Existing API, error, ordering, and state behavior outside the bug remain unchanged.
- Additional task-specific invariant: TO BE FILLED BY AGENT

## Accepted Plan

- Persistence gate: Before any source/test edit, replace the placeholder with the
  complete final Plan response. Preserve every slice exactly once and in order with
  `Change` and `Check`, plus plan-wide validation and the final
  `Plan self-check: PASS` line; never store only the selected slice or a summary.
- Complete accepted plan: TO BE FILLED BY AGENT

## Latest Snapshot

- Status: NOT_STARTED
- Change summary: TO BE FILLED BY AGENT
- Files changed: NONE
- Validation/result: NOT_RUN
- Remaining: TO BE FILLED BY AGENT
- Risk/complexity: TO BE FILLED BY AGENT