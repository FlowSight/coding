# Implement Sequential and Parallel URL Requests

## Base problem

Given an ordered list of URLs and an injected fetch function, fetch each unique
URL while preserving deterministic output. The injected function makes the
exercise testable without real network access.

## Follow-up 1: Preserve Sequential Deduplication Order

The sequential implementation does not preserve first-seen deduplication and
output order.

Acceptance criteria:

- Fetch each distinct URL exactly once.
- Preserve the order of each URL's first appearance.
- Return successes and failures in that same order.
- Empty input performs no work.

## Follow-up 2: Parallel URL Fetching

Implement parallel fetching.

Acceptance criteria:

- Independent requests may overlap.
- Results remain in first-seen input order, not completion order.
- One failed request does not discard successful results.
- The fetch function remains injected and easy to fake in tests.

## Follow-up 3: Bounded Concurrency and Error Policy

Add bounded concurrency and explicit error policy.

Acceptance criteria:

- Never exceed a positive caller-provided concurrency limit.
- Reject non-positive limits.
- Support fail-fast and collect-all modes.
- Cancellation or interruption does not leave background work unobserved.

Use the build and test command in the selected starter's README.
