# Design a Trie-Based URL Router with Wildcards

## Base problem

Implement a segment-keyed URL router. Static segments match literally and `*`
matches exactly one segment. The router supports `addRoute(pattern, handler)` and
`match(path)`, returning both the handler and registered pattern. Normalize the
root and leading or trailing slashes consistently.

## Follow-up 1: Backtrack to Wildcard Routes

Matching always chooses a static child when one exists, even when that branch
later fails and a wildcard branch would succeed.

Acceptance criteria:

- Static matches have precedence when they produce a complete match.
- Matching backtracks to a wildcard branch when the static branch dead-ends.
- `*` consumes exactly one segment.
- Root, trailing slash, and overlapping-route regression tests pass.

## Follow-up 2: Route Removal and Trie Pruning

Implement `removeRoute(pattern)`.

Acceptance criteria:

- Removing an unknown route is a no-op.
- Removing one route does not damage overlapping routes.
- Empty trie nodes are pruned.
- The duplicate-route replacement policy remains deterministic.

## Follow-up 3: Concurrent Route Updates

Make runtime reads and writes safe under concurrency.

Acceptance criteria:

- Concurrent add, remove, and match operations do not corrupt state.
- Document the chosen locking or copy-on-write strategy.
- Avoid holding an exclusive lock longer than necessary.
- Existing single-threaded behavior remains unchanged.

Use the build and test command in the selected starter's README.
