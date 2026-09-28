package core

import "sort"

type DataEvent struct {
	ID string `json:"id"`
	Type string `json:"type"`
	Payload map[string]string `json:"payload"`
}

func FilterValidEvents(input []DataEvent) []DataEvent {
	byID := make(map[string]DataEvent)
	for _, event := range input {
		if event.ID == "" { continue }
		// BUG: validation is incomplete, duplicates overwrite the first event,
		// and map keys cannot preserve first-seen order.
		byID[event.ID] = event
	}
	ids := make([]string, 0, len(byID))
	for id := range byID { ids = append(ids, id) }
	sort.Strings(ids)
	result := make([]DataEvent, 0, len(ids))
	for _, id := range ids { result = append(result, byID[id]) }
	return result
}
