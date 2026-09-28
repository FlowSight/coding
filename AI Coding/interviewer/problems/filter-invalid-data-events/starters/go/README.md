# Data-event validation starter

Go 1.22/Gin powers an event-validation API and React/Vite provides an event
review console.

In separate terminals:

```bash
(cd backend && go mod download && go run ./cmd/server)
(cd frontend && npm install && npm run dev)
```

`cd backend && go test ./internal/core` runs the focused baseline. It
intentionally exposes incomplete validation, last-duplicate selection, and
unstable order. `FilterEvents` and `FilterStream` remain follow-up APIs.
