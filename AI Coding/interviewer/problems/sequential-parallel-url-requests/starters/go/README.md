# URL request runner starter

A Go 1.22/Gin API and React/Vite request console model a small URL-checking
service.

In separate terminals:

```bash
(cd backend && go mod download && go run ./cmd/server)
(cd frontend && npm install && npm run dev)
```

`cd backend && go test ./internal/core` runs the focused baseline. Sequential
deduplication intentionally loses first-seen order. Parallel execution,
bounded concurrency, and error reporting remain incomplete follow-up APIs.
