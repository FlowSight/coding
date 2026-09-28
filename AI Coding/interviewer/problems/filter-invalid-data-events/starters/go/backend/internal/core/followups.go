package core

import "context"

type RejectionReason string
const (
	MissingID RejectionReason = "missing_id"
	UnsupportedType RejectionReason = "unsupported_type"
	MissingPayload RejectionReason = "missing_payload"
	DuplicateID RejectionReason = "duplicate_id"
)
type RejectedEvent struct { Event DataEvent `json:"event"`; Reason RejectionReason `json:"reason"` }
type FilterReport struct { Accepted []DataEvent `json:"accepted"`; Rejected []RejectedEvent `json:"rejected"` }

func FilterEvents(input []DataEvent) FilterReport {
	// TODO(report-rejection-details): include a deterministic reason for every rejected event.
	return FilterReport{Accepted: FilterValidEvents(input)}
}

type StreamResult struct { Event DataEvent; Accepted bool; Reason RejectionReason }
func FilterStream(ctx context.Context, input <-chan DataEvent) <-chan StreamResult {
	// TODO(stream-validated-events): validate and deduplicate until close or cancellation.
	output := make(chan StreamResult)
	close(output)
	return output
}
