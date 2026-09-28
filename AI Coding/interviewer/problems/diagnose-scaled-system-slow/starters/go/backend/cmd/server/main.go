package main

import (
	"interviewer/diagnose-scaled-system-slow/backend/internal/httpapi"
	"interviewer/diagnose-scaled-system-slow/backend/internal/service"
)

func main() {
	router := httpapi.NewRouter(service.NewDiagnosticsService())
	_ = router.Run(":8080")
}
