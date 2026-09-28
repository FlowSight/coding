package core

import ("reflect"; "testing")
func TestMatchBacktracksFromStaticDeadEndToWildcard(t *testing.T) {
	routes := New()
	routes.Insert("/:kind/:id", "show")
	routes.Insert("/users/new/settings", "settings")
	handler, params, ok := routes.Match("/users/new")
	if !ok || handler != "show" || !reflect.DeepEqual(params, map[string]string{"kind": "users", "id": "new"}) {
		t.Fatalf("Match() = (%q, %v, %v), want wildcard route", handler, params, ok)
	}
}
