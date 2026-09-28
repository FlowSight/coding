# Trie URL Router with Wildcards — full-stack starter

Requires Node.js 20+. The Express API manages and probes an in-memory trie; the
React route lab adds patterns and checks paths.

Run `cd backend && npm install && npm start`, then
`cd frontend && npm install && npm run dev`.

Core tests need no installed dependencies: `cd backend && node --test`. The
baseline intentionally fails only wildcard backtracking. Safe route removal and
atomic concurrent route-update APIs remain incomplete.
