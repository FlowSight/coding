package main

import ("log"; "time"; "interviewer/sliding-window-rate-limiter/backend/internal/core"; "interviewer/sliding-window-rate-limiter/backend/internal/httpapi"; "interviewer/sliding-window-rate-limiter/backend/internal/service")

func main() {
	limiter, err := core.New(3, time.Minute)
	if err != nil { log.Fatal(err) }
	_ = httpapi.NewRouter(service.NewLimiterService(limiter)).Run(":8080")
}
