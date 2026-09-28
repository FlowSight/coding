package main

import ("net/http"; "interviewer/sequential-parallel-url-requests/backend/internal/httpapi"; "interviewer/sequential-parallel-url-requests/backend/internal/service")

func main() { _ = httpapi.NewRouter(service.NewRequestService(http.DefaultClient)).Run(":8080") }
