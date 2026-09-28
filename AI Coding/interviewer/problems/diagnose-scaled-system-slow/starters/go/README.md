# Scaled-system diagnostics starter

This seed pairs a Go 1.22/Gin API with a React/Vite diagnostics dashboard.

In separate terminals:

```bash
(cd backend && go mod download && go run ./cmd/server)
(cd frontend && npm install && npm run dev)
```

Run the focused baseline with `cd backend && go test ./internal/core`. It
intentionally fails because shard samples are collapsed into one bucket.
`RankHypotheses` and `RecommendProbes` remain descriptive follow-up APIs.
