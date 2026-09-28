package core

import "context"

type Mode int
const ( Sequential Mode = iota; Parallel )
type Options struct { Mode Mode; MaxConcurrency int }
type ErrorReport struct { URL string; Err error }
type Report struct { Results []Result; Errors []ErrorReport }

func RequestAll(ctx context.Context, urls []string, requester Requester, options Options) Report {
	// TODO(parallel-url-fetching): honor Parallel mode with deterministic result order.
	// TODO(bounded-concurrency-error-policy): enforce MaxConcurrency and report errors separately.
	return Report{Results: RequestSequential(ctx, urls, requester)}
}
