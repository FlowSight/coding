# Filter Invalid Data Events — full-stack starter

Requires Node.js 20+. The Express ingestion API filters a submitted event batch,
while the React workbench edits JSON and displays accepted events.

Run `cd backend && npm install && npm start`, then
`cd frontend && npm install && npm run dev`.

Core tests require no dependencies: `cd backend && node --test`. The baseline
intentionally fails only stable first-occurrence deduplication. Rejection-detail
and validated-event-stream APIs remain incomplete.
