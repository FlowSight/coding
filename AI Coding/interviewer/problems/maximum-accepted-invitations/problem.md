# Maximum Number of Accepted Invitations

## Base problem

There are `m` boys and `n` girls. `grid[boy][girl] == 1` means that the pair can
attend together. Each person can be part of at most one accepted invitation.

The codebase contains a bipartite-matching implementation and a small test
runner in your selected language. Work through the follow-ups in order.
Preserve the existing public API unless a follow-up explicitly extends it.

## Follow-up 1: Repair Augmenting-Path Search

The matcher returns a result smaller than the true maximum for some graphs where
an earlier match must be rerouted.

Acceptance criteria:

- Find and fix the defect without replacing the matching algorithm.
- Existing tests pass.
- Add or preserve a regression case that requires an augmenting path.
- Empty inputs and rectangular grids remain safe.

## Follow-up 2: Return Match Assignments

Implement `maximumInvitationsWithAssignments`.

Acceptance criteria:

- Return the maximum invitation count and the selected `(boy, girl)` pairs.
- Every returned pair corresponds to a `1` in the input grid.
- No boy or girl appears in more than one returned pair.
- The number of pairs equals the returned count.
- `maximumInvitations` remains supported.

## Follow-up 3: Incremental Compatibility Updates

Complete `IncrementalInvitationMatcher` so callers can add compatibility edges
and query the current maximum assignment.

Acceptance criteria:

- `addCompatibility(boy, girl)` validates both indices.
- Adding an existing edge is idempotent.
- A later `currentMatching()` reflects every successful addition.
- Repeated reads without an update return the same result.
- The returned assignment obeys all Return Match Assignments validity rules.

Use the build and test command in the selected starter's README.
