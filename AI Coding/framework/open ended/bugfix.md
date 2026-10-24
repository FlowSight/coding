# Bug-Fix and Stabilization Plan

Use this workflow when a codebase already has bugs and you need to stabilize it
before implementing a feature. Do not try to fix every bug. Stabilize only the
minimum path required to develop and verify the feature safely.

## 0. Map the relevant codebase

For a large or unfamiliar repository, first locate the relevant architecture,
entry points, code path, and focused test commands. Do not try to understand
every file.

```text
Map this repo for <bug/feature>: key modules, entry points, relevant code flow,
and the smallest build/test commands. Do not modify files or list every file.
Put analysis into ./repo_basic.md
```

## 1. Establish the baseline

Before changing anything:

1. Run the application.
2. Run the existing tests.
3. Record what currently works.
4. Record existing test failures and reproducible bugs.
5. Identify whether those failures block the intended feature.

State the reason aloud:

> Before adding behavior, I will establish the baseline so I can distinguish
> existing failures from regressions introduced by my changes.

## 2. Ask AI to triage, not fix everything

```text
Inspect the repository and the current test failures. Do not modify files yet.

For each confirmed bug, report:
- evidence or reproduction,
- relation to <feature>: blocking, related, or unrelated,
- impact: critical, high, medium, or low,
- smallest safe fix,
- recommendation: fix now, escalate, or defer.

Keep it concise and prioritize what must happen before <feature>.
```

AI can provide the analysis, but make the final prioritization decision
yourself.

## 3. Select only prerequisite bugs

| Bug type | Action |
|---|---|
| Application does not start | Fix first |
| Test infrastructure is broken | Fix first |
| Bug affects the feature's code path | Usually fix first |
| Bug makes feature tests unreliable | Fix first |
| Security or data-corruption bug | Fix first or immediately escalate |
| Minor unrelated UI problem | Defer |
| Unrelated failing test with a known cause | Record and defer |
| Large architectural problem | Discuss scope before fixing |

State the scope boundary:

> I found three existing issues. The task-loading failure blocks the feature, so
> I will fix it first. The other two are unrelated and will be documented rather
> than included in this change.

<details>
<summary>How to prioritize bugs before the feature</summary>

Classify each confirmed bug using two independent dimensions:

- **Relationship** determines sequencing: blocking, related, or unrelated.
- **Impact** determines urgency: critical, high, medium, or low.

Use this order:

1. Fix or escalate critical and high-impact bugs regardless of feature
   relevance.
2. Fix anything blocking development or reliable verification.
3. Fix medium-impact correctness bugs in or near the feature path.
4. Implement the feature.
5. Fix unrelated medium-impact bugs first only when they are small,
   well-understood, and expected within the interview scope; otherwise document
   and defer them.
6. Defer unrelated low-impact bugs.

| Impact | Blocking or related | Unrelated |
|---|---|---|
| Critical | Fix immediately | Fix or escalate immediately |
| High | Fix first | Fix first or confirm scope |
| Medium | Fix first | Fix if bounded; otherwise document and defer |
| Low | Fix only if blocking | Defer |

Before spending interview time on a bug, ensure it is:

1. **Confirmed:** reproduced or supported by strong evidence.
2. **Important:** has meaningful correctness, security, or user impact.
3. **Bounded:** can likely be fixed and tested in reasonable time.

> Severity sets urgency, dependency sets sequencing, and available time limits
> scope.

</details>

## 4. Fix each selected bug with a regression test

For each selected bug:

1. Reproduce the failure.
2. Add or identify a test that fails for the correct reason.
3. Make the smallest root-cause fix.
4. Run the focused test.
5. Run the relevant baseline tests.
6. Avoid unrelated refactoring.

```text
Fix only the <identified bug>.

First add a regression test that reproduces the failure, then implement the
smallest root-cause fix. Avoid refactoring or changing unrelated behavior.

Run the focused test and report:
- root cause,
- files changed,
- test result,
- remaining related risks.
```

Keep bug-fix changes conceptually separate from feature changes. Prefer a
separate commit when the interview workflow allows it.

## 5. Re-establish a trustworthy baseline

Before starting the feature, confirm:

- The blocking bug is fixed.
- Its regression test passes.
- The fix did not introduce new failures.
- Remaining failures are understood, documented, and unrelated.

The entire repository does not need to be clean if the remaining failures are
pre-existing and do not affect the feature.

Use a clear transition:

> The prerequisite path is now stable and covered by a regression test. Two
> unrelated baseline failures remain, but neither intersects with this feature.
> I will now proceed with the feature implementation.

## 6. Move to feature implementation

```text
Map the relevant codebase
    -> Establish baseline
    -> Triage bugs
    -> Fix selected high-priority and blocking bugs with regression tests
    -> Re-run the relevant baseline
    -> Perform feature reconnaissance
    -> Approve or correct the approach
    -> Implement the feature and tests together
    -> Review the diff
    -> Validate and demonstrate
```

Continue with the workflow in [feature.md](./feature.md).

## Keep the work distinguishable

Clearly separate:

- **Baseline behavior:** What was already broken?
- **Prerequisite fix:** What had to be repaired and why?
- **Feature behavior:** What new capability was added?
- **Verification:** Which tests prove each part?

The goal is not "fix all bugs, then build." The goal is:

> Stabilize the minimum required path, then deliver the feature.