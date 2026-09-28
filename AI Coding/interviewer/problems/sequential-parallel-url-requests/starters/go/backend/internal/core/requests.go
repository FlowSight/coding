package core

import ("context"; "sort")

type Requester interface { Do(ctx context.Context, url string) (Response, error) }
type Response struct { StatusCode int `json:"statusCode"`; Body []byte `json:"body"` }
type Result struct { URL string `json:"url"`; Response Response `json:"response"`; Err error `json:"-"` }

func RequestSequential(ctx context.Context, urls []string, requester Requester) []Result {
	unique := make(map[string]struct{}, len(urls))
	for _, url := range urls { unique[url] = struct{}{} }
	ordered := make([]string, 0, len(unique))
	for url := range unique { ordered = append(ordered, url) }
	// BUG: deduplication must retain first-seen input order, not sorted order.
	sort.Strings(ordered)
	results := make([]Result, 0, len(ordered))
	for _, url := range ordered {
		response, err := requester.Do(ctx, url)
		results = append(results, Result{URL: url, Response: response, Err: err})
	}
	return results
}
