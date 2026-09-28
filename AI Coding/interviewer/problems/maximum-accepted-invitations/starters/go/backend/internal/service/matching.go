package service

import "interviewer/maximum-accepted-invitations/backend/internal/core"

type MatchingService struct{}
func NewMatchingService() *MatchingService { return &MatchingService{} }
func (s *MatchingService) Maximum(grid [][]int) int { return core.MaximumInvitations(grid) }
