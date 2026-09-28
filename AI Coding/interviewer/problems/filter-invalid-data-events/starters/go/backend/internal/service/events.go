package service

import "interviewer/filter-invalid-data-events/backend/internal/core"

type EventService struct{}
func NewEventService() *EventService { return &EventService{} }
func (s *EventService) Filter(events []core.DataEvent) []core.DataEvent {
	return core.FilterValidEvents(events)
}
