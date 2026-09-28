# Trie URL router starter

A Go 1.22/Gin API exposes a route-trie playground used by a React/Vite
frontend.

In separate terminals:

```bash
(cd backend && go mod download && go run ./cmd/server)
(cd frontend && npm install && npm run dev)
```

Run `cd backend && go test ./internal/core` for the focused baseline. Wildcard
backtracking after a static dead end is intentionally missing. Route removal
and concurrency safety remain incomplete follow-up APIs.
