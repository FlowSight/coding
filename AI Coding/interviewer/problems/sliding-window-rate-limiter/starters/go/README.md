# Sliding-window limiter starter

This seed provides a Go 1.22/Gin decision API and a React/Vite traffic
simulator.

In separate terminals:

```bash
(cd backend && go mod download && go run ./cmd/server)
(cd frontend && npm install && npm run dev)
```

Run `cd backend && go test ./internal/core` for the focused baseline. A
timestamp exactly on the window boundary is intentionally retained. Per-key
limits and concurrent stale-key cleanup remain incomplete follow-up APIs.
