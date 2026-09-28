package core

import ("fmt"; "time")
type Limiter struct { limit int; window time.Duration; timestamps []time.Time }
func New(limit int, window time.Duration) (*Limiter, error) {
	if limit <= 0 { return nil, fmt.Errorf("limit must be positive") }
	if window <= 0 { return nil, fmt.Errorf("window must be positive") }
	return &Limiter{limit: limit, window: window}, nil
}
func (l *Limiter) Allow(now time.Time) bool {
	cutoff := now.Add(-l.window)
	firstActive := 0
	for firstActive < len(l.timestamps) && l.timestamps[firstActive].Before(cutoff) { firstActive++ }
	l.timestamps = l.timestamps[firstActive:]
	// BUG: a timestamp exactly at cutoff is outside [now-window, now).
	if len(l.timestamps) >= l.limit { return false }
	l.timestamps = append(l.timestamps, now)
	return true
}
