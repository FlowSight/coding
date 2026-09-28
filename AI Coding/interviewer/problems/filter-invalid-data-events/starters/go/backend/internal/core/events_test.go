package core

import ("reflect"; "testing")

func TestFilterValidEventsValidatesDeduplicatesAndPreservesOrder(t *testing.T) {
	firstB := DataEvent{ID: "b", Type: "created", Payload: map[string]string{"version": "first"}}
	a := DataEvent{ID: "a", Type: "updated", Payload: map[string]string{"version": "one"}}
	secondB := DataEvent{ID: "b", Type: "updated", Payload: map[string]string{"version": "second"}}
	invalid := DataEvent{ID: "bad", Type: "deleted", Payload: map[string]string{"version": "one"}}
	got, want := FilterValidEvents([]DataEvent{firstB, a, secondB, invalid}), []DataEvent{firstB, a}
	if !reflect.DeepEqual(got, want) { t.Fatalf("FilterValidEvents() = %#v, want %#v", got, want) }
}
