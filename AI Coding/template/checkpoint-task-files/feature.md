# Task <ID>: <Feature Title>

- Type: FEATURE
- Status: DRAFT
- Task: <fill or TO BE FILLED BY AGENT>
- Known input/output/error contract: <fill or TO BE FILLED BY AGENT>
- Unknowns: TO BE FILLED BY AGENT

## Acceptance

- Requested happy-path behavior works end to end.
- Required boundary and error behavior works.
- New behavior has a focused validation check.
- All previously passing tests still pass.
- Task-specific acceptance: TO BE FILLED BY AGENT

## Constraints

- After every code or test change, run all exposed/available tests before another change.
- If tests are hidden/unavailable, run every exposed test and record the limitation.
- Do not change existing tests or public contracts unless the requirement changes them.
- Preserve existing behavior outside the feature.
- Follow existing repository architecture, style, and patterns.
- Avoid unrelated refactors or speculative abstractions.
- Additional constraints/non-goals: TO BE FILLED BY AGENT

## Agent Context

- Current gap: TO BE FILLED BY AGENT
- Relevant code/path: TO BE FILLED BY AGENT
- Ordering/state/compatibility: TO BE FILLED BY AGENT
- Evidence: TO BE FILLED BY AGENT
- Available validation: TO BE FILLED BY AGENT
- Behavior trace, only if task is unclear: TO BE FILLED BY AGENT

## Invariants

- Previously supported behavior remains unchanged unless explicitly superseded.
- Existing tests and public API/error contracts remain valid.
- Existing ordering, state, and side-effect rules remain valid.
- Additional task-specific invariant: TO BE FILLED BY AGENT

## Accepted Plan

- Persistence gate: Before any source/test edit, replace the placeholder with the
  complete final Plan response. Preserve every slice exactly once and in order with
  `Change` and `Check`, plus plan-wide validation and the final
  `Plan self-check: PASS` line; never store only the selected slice or a summary.
- Complete accepted plan: TO BE FILLED BY AGENT

## Latest Snapshot

- Status: NOT_STARTED
- Delivered behavior: TO BE FILLED BY AGENT
- Files changed: NONE
- Validation/result: NOT_RUN
- Remaining: TO BE FILLED BY AGENT
- Risk/complexity: TO BE FILLED BY AGENT