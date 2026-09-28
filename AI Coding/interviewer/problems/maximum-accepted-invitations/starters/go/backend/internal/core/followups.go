package core

import "fmt"

type Assignment struct { Boy int `json:"boy"`; Girl int `json:"girl"` }
type MatchResult struct { Count int `json:"count"`; Assignments []Assignment `json:"assignments"` }

func MaximumInvitationsWithAssignments(grid [][]int) MatchResult {
	// TODO(return-match-assignments): return selected pairs and count.
	return MatchResult{Count: MaximumInvitations(grid)}
}

type IncrementalInvitationMatcher struct { grid [][]int }
func NewIncrementalInvitationMatcher(grid [][]int) *IncrementalInvitationMatcher {
	copyGrid := make([][]int, len(grid))
	for i := range grid { copyGrid[i] = append([]int(nil), grid[i]...) }
	return &IncrementalInvitationMatcher{grid: copyGrid}
}
func (m *IncrementalInvitationMatcher) AddCompatibility(boy, girl int) error {
	// TODO(incremental-compatibility-updates): validate, add idempotently, and invalidate cached state.
	return fmt.Errorf("incremental compatibility updates are not implemented")
}
func (m *IncrementalInvitationMatcher) CurrentMatching() MatchResult {
	return MaximumInvitationsWithAssignments(m.grid)
}
