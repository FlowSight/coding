package core

import "strings"
type node struct { static map[string]*node; wildcard *node; wildcardName, handler string }
type Router struct { root *node }
func New() *Router { return &Router{root: &node{static: make(map[string]*node)}} }
func (r *Router) Insert(pattern, handler string) {
	current := r.root
	for _, segment := range segments(pattern) {
		if strings.HasPrefix(segment, ":") {
			if current.wildcard == nil { current.wildcard = &node{static: make(map[string]*node)} }
			current.wildcardName = strings.TrimPrefix(segment, ":")
			current = current.wildcard
		} else {
			if current.static[segment] == nil { current.static[segment] = &node{static: make(map[string]*node)} }
			current = current.static[segment]
		}
	}
	current.handler = handler
}
func (r *Router) Match(path string) (string, map[string]string, bool) {
	return match(r.root, segments(path), 0, make(map[string]string))
}
func match(current *node, path []string, index int, params map[string]string) (string, map[string]string, bool) {
	if index == len(path) { return current.handler, params, current.handler != "" }
	if child := current.static[path[index]]; child != nil {
		// BUG: a static dead end must backtrack and try the wildcard sibling.
		return match(child, path, index+1, params)
	}
	if current.wildcard != nil {
		captured := cloneParams(params)
		captured[current.wildcardName] = path[index]
		return match(current.wildcard, path, index+1, captured)
	}
	return "", nil, false
}
