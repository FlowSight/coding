package core

import ("context"; "reflect"; "testing")
type recordingRequester struct { calls []string }
func (r *recordingRequester) Do(_ context.Context, url string) (Response, error) {
	r.calls = append(r.calls, url)
	return Response{StatusCode: 200, Body: []byte(url)}, nil
}
func TestRequestSequentialDeduplicatesInFirstSeenOrder(t *testing.T) {
	requester := &recordingRequester{}
	results := RequestSequential(context.Background(), []string{"https://b.example", "https://a.example", "https://b.example"}, requester)
	got := make([]string, 0, len(results))
	for _, result := range results { got = append(got, result.URL) }
	want := []string{"https://b.example", "https://a.example"}
	if !reflect.DeepEqual(got, want) || !reflect.DeepEqual(requester.calls, want) { t.Fatalf("order = %v, calls = %v, want %v", got, requester.calls, want) }
}
