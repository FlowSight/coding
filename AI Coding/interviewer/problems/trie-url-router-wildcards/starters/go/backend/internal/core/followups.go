package core

import "strings"
func (r *Router) Remove(pattern string) bool {
	// TODO(route-removal-trie-pruning): remove the route and prune unused nodes.
	return false
}
func segments(path string) []string {
	trimmed := strings.Trim(path, "/")
	if trimmed == "" { return nil }
	return strings.Split(trimmed, "/")
}
func cloneParams(params map[string]string) map[string]string {
	copy := make(map[string]string, len(params))
	for key, value := range params { copy[key] = value }
	return copy
}
// TODO(concurrent-route-updates): make Insert, Match, and Remove safe for concurrent callers.
