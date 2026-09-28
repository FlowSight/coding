# Sequential and Parallel URL Requests — full-stack starter

Requires Node.js 20+. The Express API schedules URL jobs through an injected
request adapter; the React console submits newline-separated URLs.

Run `cd backend && npm install && npm start`, then
`cd frontend && npm install && npm run dev`.

Core tests use an injected requester and need no dependencies:
`cd backend && node --test`. The baseline intentionally fails only the
dedupe/order regression. Stable parallel fetching and bounded-concurrency
error-reporting APIs remain incomplete.
