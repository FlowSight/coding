# Filter Invalid Data Events

## Base problem

Filter a batch of data events against required fields, an event-type allow-list,
an inclusive timestamp range, and duplicate IDs. Preserve the first valid
occurrence of each ID and retain stable input order.

## Follow-up 1: Validate Before Stable Deduplication

The current filter applies validation and deduplication in the wrong order,
causing valid later events to disappear or output order to change.

Acceptance criteria:

- Invalid events never reserve an ID.
- The first valid event for an ID wins.
- Output order matches the accepted events' input order.
- Timestamp boundaries are inclusive.

## Follow-up 2: Report Rejection Details

Return rejection details alongside accepted events.

Acceptance criteria:

- Every rejected event has one or more stable reason codes.
- Reason ordering is deterministic.
- Rejection reporting does not change accepted-event behavior.
- Duplicate reasons distinguish duplicate valid events from malformed events.

## Follow-up 3: Stream Validated Events

Add a streaming filter API.

Acceptance criteria:

- Processing chunks yields the same results as one batch in the same order.
- Deduplication state is explicit and bounded by a documented policy.
- Callers can reset or checkpoint state.
- Batch behavior remains supported.

Use the build and test command in the selected starter's README.
