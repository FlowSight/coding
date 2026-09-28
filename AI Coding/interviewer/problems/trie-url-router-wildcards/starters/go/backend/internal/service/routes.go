package service

import "interviewer/trie-url-router-wildcards/backend/internal/core"
type Match struct { Handler string `json:"handler"`; Params map[string]string `json:"params"`; Found bool `json:"found"` }
type RouteService struct { routes *core.Router }
func NewRouteService(routes *core.Router) *RouteService { return &RouteService{routes: routes} }
func (s *RouteService) Add(pattern, handler string) { s.routes.Insert(pattern, handler) }
func (s *RouteService) Match(path string) Match {
	handler, params, found := s.routes.Match(path)
	return Match{handler, params, found}
}
