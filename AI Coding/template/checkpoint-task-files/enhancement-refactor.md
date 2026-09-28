# Task <ID>: <Enhancement or Refactor Title>

- Type: ENHANCEMENT_REFACTOR
- Status: DRAFT
- Task: <fill or TO BE FILLED BY AGENT>
- Preservation target (behavior/API): <fill or TO BE FILLED BY AGENT>
- Unknowns: TO BE FILLED BY AGENT

## Acceptance

- Required structural or maintainability improvement is complete.
- Existing observable behavior and public API remain unchanged unless specified.
- Characterization and regression checks pass.
- All previously passing tests still pass.
- Task-specific acceptance: TO BE FILLED BY AGENT

## Constraints

- After every code or test change, run all exposed/available tests before another change.
- If tests are hidden/unavailable, run every exposed test and record the limitation.
- Do not change, remove, or weaken tests merely to complete the refactor.
- Preserve public contracts, data/state rules, and compatibility.
- Follow existing repository architecture, style, and patterns.
- Avoid unrelated cleanup or speculative abstractions.
- Additional constraints/non-goals: TO BE FILLED BY AGENT

## Agent Context

- Current structure/boundary: TO BE FILLED BY AGENT
- Relevant code/path: TO BE FILLED BY AGENT
- Compatibility/migration: TO BE FILLED BY AGENT
- Evidence: TO BE FILLED BY AGENT
- Available validation: TO BE FILLED BY AGENT
- Behavior trace, only if task is unclear: TO BE FILLED BY AGENT

## Invariants

- Existing observable behavior and public APIs remain unchanged unless specified.
- All previously passing tests remain passing.
- Existing data/state and error contracts remain valid.
- Additional task-specific invariant: TO BE FILLED BY AGENT

## Accepted Plan

- Persistence gate: Before any source/test edit, replace the placeholder with the
  complete final Plan response. Preserve every slice exactly once and in order with
  `Change` and `Check`, plus plan-wide validation and the final
  `Plan self-check: PASS` line; never store only the selected slice or a summary.
- Complete accepted plan: TO BE FILLED BY AGENT

## Latest Snapshot

- Status: NOT_STARTED
- Preserved/added behavior: TO BE FILLED BY AGENT
- Files changed: NONE
- Validation/result: NOT_RUN
- Remaining: TO BE FILLED BY AGENT
- Risk/complexity: TO BE FILLED BY AGENT