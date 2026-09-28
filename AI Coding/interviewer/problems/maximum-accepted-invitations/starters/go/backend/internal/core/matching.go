package core

func MaximumInvitations(grid [][]int) int {
	girls := 0
	for _, row := range grid { if len(row) > girls { girls = len(row) } }
	matchedBoy := make([]int, girls)
	for girl := range matchedBoy { matchedBoy[girl] = -1 }
	count := 0
	for boy := range grid {
		seen := make([]bool, girls)
		if findInvitation(grid, boy, seen, matchedBoy) { count++ }
	}
	return count
}

func findInvitation(grid [][]int, boy int, seen []bool, matchedBoy []int) bool {
	for girl, compatible := range grid[boy] {
		if compatible == 0 || seen[girl] { continue }
		seen[girl] = true
		// BUG: an occupied girl must be allowed to reroute her current match.
		if matchedBoy[girl] == -1 { matchedBoy[girl] = boy; return true }
	}
	return false
}
