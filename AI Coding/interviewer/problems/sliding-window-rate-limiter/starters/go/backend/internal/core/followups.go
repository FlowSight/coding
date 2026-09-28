package core

import ("fmt"; "time")
type KeyedLimiter struct { limit int; window time.Duration }
func NewKeyed(limit int, window time.Duration) (*KeyedLimiter, error) {
	if limit <= 0 || window <= 0 { return nil, fmt.Errorf("limit and window must be positive") }
	// TODO(per-key-rate-limits): initialize independent windows for each key.
	return &KeyedLimiter{limit: limit, window: window}, nil
}
func (l *KeyedLimiter) Allow(key string, now time.Time) bool {
	// TODO(per-key-rate-limits): enforce configured limit independently for key.
	return false
}
func (l *KeyedLimiter) Cleanup(now time.Time) int {
	// TODO(stale-key-cleanup): safely remove idle keys during concurrent Allow calls.
	return 0
}
