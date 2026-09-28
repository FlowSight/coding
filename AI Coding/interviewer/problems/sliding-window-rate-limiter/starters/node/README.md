# Sliding Window Rate Limiter — full-stack starter

Requires Node.js 20+. The Express API owns a limiter instance and the React
console lets an operator submit timestamped requests for a key.

Run `cd backend && npm install && npm start`, then in another terminal run
`cd frontend && npm install && npm run dev`.

Core tests are dependency-free: `cd backend && node --test`. The baseline
intentionally fails only the exact-window-boundary regression. The per-key
cleanup and concurrent-admission APIs remain incomplete.
