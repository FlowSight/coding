package main

import ("interviewer/maximum-accepted-invitations/backend/internal/httpapi"; "interviewer/maximum-accepted-invitations/backend/internal/service")

func main() { _ = httpapi.NewRouter(service.NewMatchingService()).Run(":8080") }
