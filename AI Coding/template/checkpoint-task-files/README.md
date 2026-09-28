# Checkpoint Task File Templates

Create one scratchpad before every checkpoint. For task `T1`, create
`.interview/tasks/task_T1.md` and copy the matching template:

- [Bug fix](bug.md)
- [Feature](feature.md)
- [Performance optimization](optimization.md)
- [Enhancement or refactor](enhancement-refactor.md)

If the platform cannot create folders, use `task_T1.md` at the repository root and
use that exact path in every prompt.

## Per-Task Use

1. Assign `T1`, `T2`, and so on.
2. Copy the matching template, or use Prompt 4's short table-free AI seed. This should
   take under 30 seconds; you do not type any Plan tables.
3. Fill `Task` and whatever else you know. Leave every other value exactly
   `TO BE FILLED BY AGENT`.
4. If the task is clear, send Prompt 4's `COMPLETE CURRENT TASK`; do not run discovery
   or spawn subagents.
5. Only when the task or acceptance is unclear, send `DISCOVER UNCLEAR TASK`. The
   parent Agent may internally spawn two read-only workers; you do not launch them.
6. Resolve `AMBIGUOUS`. Before Plan mode, spend 30-60 seconds forming and stating your
   own acceptance condition, simplest approach/flow order, and predicted first check.
7. Send `CURRENT_TASK: <path>` in Plan mode.
8. Plan mode returns all slices at once. Compare that response with your direction,
   accept deviations only with evidence, and reject unnecessary architecture. Review
   the complete response aloud before
   accepting it: task coverage, sensible part/flow order, `Change` and `Check` for
   every slice, test rules, and the final `Plan self-check: PASS` line.
9. Choose exactly one persistence method. By default, run Prompt 4's dedicated
   `PERSIST ACCEPTED PLAN ONLY` Agent turn. Copy manually only when that is faster or
   Agent mode cannot reliably see the Plan response. Never do both.
10. Verify every slice appears exactly once and in order with `Change` and `Check`,
   plan-wide test/final-validation rules, and `Plan self-check: PASS`. Persistence
   must not edit source, tests, configuration, or build files.
11. Only after that gate passes, start a separate Agent turn naming one persisted slice.
   The implementation turn leaves **Accepted Plan** unchanged and replaces only
   **Latest Snapshot** after validation.
12. After every code or test change, run every available test before another change.
   If tests are hidden, run all exposed tests and record that limitation.

If the plan changes, replace **Accepted Plan** with the complete revised plan and pass
the persistence gate again before implementing another slice. Never store only the
selected slice or a summary of the plan.

The task file is a scratchpad, not proof. Verify cited code and observable results
before accepting claims.