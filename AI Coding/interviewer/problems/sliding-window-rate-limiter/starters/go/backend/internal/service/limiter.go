package service

import ("time"; "interviewer/sliding-window-rate-limiter/backend/internal/core")
type LimiterService struct { limiter *core.Limiter }
func NewLimiterService(limiter *core.Limiter) *LimiterService { return &LimiterService{limiter: limiter} }
func (s *LimiterService) Allow(now time.Time) bool { return s.limiter.Allow(now) }
