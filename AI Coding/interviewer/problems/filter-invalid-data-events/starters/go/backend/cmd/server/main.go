package main

import (
	"interviewer/filter-invalid-data-events/backend/internal/httpapi"
	"interviewer/filter-invalid-data-events/backend/internal/service"
)

func main() { _ = httpapi.NewRouter(service.NewEventService()).Run(":8080") }
