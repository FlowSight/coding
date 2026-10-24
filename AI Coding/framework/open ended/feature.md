# Feature Implementation Plan

## 1. Choose the feature yourself

<details>
<summary>How to select a feature</summary>

1. User value : does it solve a real user problem
2. Fit with the existing architecture
3. Ability to deliver a small, demonstrable vertical slice
4. Low dependency and migration risk
5. Testability within the available time

</details>

State the decision and trade-off aloud:

> I considered A, B, and C. I will implement B because it provides visible user
> value, fits the existing architecture, and can be completed and tested within
> the remaining time.

Avoid asking AI to choose unless feature discovery is explicitly part of the
interview.

## 2. Ask AI for bounded reconnaissance

Do not request implementation or a large design document yet. Run below in plan mode

```text
Inspect the relevant code paths for feature <X>. Do not modify files yet.
Return:
1. relevant files and the current request/data flow,
2. the smallest viable implementation,
3. assumptions and edge cases,
4. tests to add,
5. decisions requiring my approval.

Keep the response concise and do not create design documents.
```

## 3. Review and refine the approach

Before implementation, confirm that you can explain:

- Where the change belongs
- How data flows through it
- What can fail
- Which observable behaviors the tests will verify
- Why the scope is appropriate for the available time

Make a meaningful correction when needed. Do not disagree with AI merely for
appearance.

Example:

> I agree with the integration point, but I do not want a new abstraction yet
> because there is only one consumer. I will keep the logic local and extract it
> if another use case appears.

## 4. Request implementation and tests together

Run below in agent mode :

```text
Implement the agreed smallest vertical slice for <X> and its focused tests. Comment around key working snippets of a method/code.
Preserve existing behavior, follow repository patterns, and avoid unrelated
refactoring. Run the smallest relevant validation.

When finished, report:
- files changed,
- behavior implemented,
- tests run and results,
- assumptions or remaining risks.
```

Tests are part of the implementation contract, not a later cleanup prompt.
While AI works, inspect the relevant code yourself so that you can review and
explain the resulting changes.

## 5. Review the actual diff

Check:

- Does the implementation match the agreed scope?
- Are all changes necessary?
- Did AI introduce unnecessary abstractions?
- Are failures and boundary cases handled explicitly?
- Do tests verify observable behavior rather than implementation details?
- Can you explain every important change?

If changes are needed, give one precise amendment request:

```text
The happy path is correct. Amend only these points (for example only):
1. validate <X> before mutating <Y>,
2. add a test for <Z>,
3. remove abstraction <Q> because it has only one caller.

Re-run the focused tests and report the results.
```

## 6. Demonstrate and summarize

Run or show the focused test command. Summarize:

1. The user-visible behavior added
2. The key design decision and its trade-off
3. The tests proving the behavior
4. Known limitations or the next production-hardening step

## When to use a parallel review chat

Use a second reviewer only for changes involving:

- An unfamiliar or large codebase
- Concurrency or state consistency
- Authentication or security-sensitive behavior
- Complex data migrations
- Several architectural layers

Ask it to review the implementation diff rather than redesign the feature:

```text
Review the current diff for correctness, missing edge cases, unnecessary
complexity, and weak tests. Return only high-confidence findings ordered by
impact. Do not modify files.
```

For a small feature, coordinating another chat may take longer than reviewing
the diff directly.

## Target loop

```text
Choose feature yourself
    -> AI reconnaissance: files, minimal approach, tests, open decisions
    -> Approve or correct the approach aloud
    -> AI implements code and tests together
    -> Review and explain the diff
    -> Make one focused correction if needed
    -> Run tests and demonstrate behavior
```

Optimize for low delegation distance: understand, choose, and defend what AI
implements rather than only optimizing for elapsed time.