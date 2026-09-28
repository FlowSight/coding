# Implement Sliding-Window Rate Limiter Function

## Base problem

Implement a sliding-window limiter that accepts at most `limit` requests during
the interval `(now - window, now]`. Timestamps supplied by the caller are
monotonic. Avoid sleeping or reading the system clock inside the core logic.

## Follow-up 1: Correct the Sliding-Window Boundary

The current eviction rule mishandles a request exactly at the open lower
boundary of the window.

Acceptance criteria:

- Requests at `now - window` are expired.
- Requests newer than that boundary still count.
- Rejected requests do not consume capacity.
- Invalid limits, windows, or non-monotonic timestamps fail explicitly.

## Follow-up 2: Enforce Per-Key Rate Limits

Support independent limits per key.

Acceptance criteria:

- Activity for one key cannot consume another key's capacity.
- Each key retains exact sliding-window semantics.
- The API exposes current in-window usage for a key.
- Empty and previously unseen keys behave deterministically.

## Follow-up 3: Clean Up Stale Keys Safely

Add stale-key cleanup and safe concurrent use.

Acceptance criteria:

- Idle key state can be reclaimed without changing active decisions.
- Concurrent checks cannot admit more requests than the configured limit.
- Define lock granularity and cleanup complexity.
- Tests use supplied timestamps and remain deterministic.

Use the build and test command in the selected starter's README.
