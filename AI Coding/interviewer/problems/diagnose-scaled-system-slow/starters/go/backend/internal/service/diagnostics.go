package service

import "interviewer/diagnose-scaled-system-slow/backend/internal/core"

type DiagnosticsService struct{}

func NewDiagnosticsService() *DiagnosticsService { return &DiagnosticsService{} }

func (s *DiagnosticsService) Summarize(samples []core.MetricSample) []core.ShardSummary {
	return core.AggregateByShard(samples)
}
