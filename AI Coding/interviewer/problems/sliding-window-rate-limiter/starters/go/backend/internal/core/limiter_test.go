package core

import ("testing"; "time")
func TestAllowExpiresRequestAtExactWindowBoundary(t *testing.T) {
	limiter, err := New(1, time.Minute)
	if err != nil { t.Fatal(err) }
	start := time.Date(2026, 1, 1, 0, 0, 0, 0, time.UTC)
	if !limiter.Allow(start) { t.Fatal("first request should be allowed") }
	if !limiter.Allow(start.Add(time.Minute)) { t.Fatal("request exactly one window later should be allowed") }
}
