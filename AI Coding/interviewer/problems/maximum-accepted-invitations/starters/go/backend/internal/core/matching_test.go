package core

import "testing"

func TestMaximumInvitationsReroutesEarlierMatch(t *testing.T) {
	grid := [][]int{{1, 1}, {1, 0}}
	if got := MaximumInvitations(grid); got != 2 { t.Fatalf("MaximumInvitations() = %d, want 2", got) }
}
