package main

import ("interviewer/trie-url-router-wildcards/backend/internal/core"; "interviewer/trie-url-router-wildcards/backend/internal/httpapi"; "interviewer/trie-url-router-wildcards/backend/internal/service")

func main() { _ = httpapi.NewRouter(service.NewRouteService(core.New())).Run(":8080") }
