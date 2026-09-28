package service

import ("context"; "io"; "net/http"; "interviewer/sequential-parallel-url-requests/backend/internal/core")

type HTTPRequester struct { client *http.Client }
func (r HTTPRequester) Do(ctx context.Context, url string) (core.Response, error) {
	request, err := http.NewRequestWithContext(ctx, http.MethodGet, url, nil)
	if err != nil { return core.Response{}, err }
	response, err := r.client.Do(request)
	if err != nil { return core.Response{}, err }
	defer response.Body.Close()
	body, err := io.ReadAll(response.Body)
	return core.Response{StatusCode: response.StatusCode, Body: body}, err
}
type RequestService struct { requester HTTPRequester }
func NewRequestService(client *http.Client) *RequestService { return &RequestService{requester: HTTPRequester{client}} }
func (s *RequestService) Run(ctx context.Context, urls []string) []core.Result { return core.RequestSequential(ctx, urls, s.requester) }
