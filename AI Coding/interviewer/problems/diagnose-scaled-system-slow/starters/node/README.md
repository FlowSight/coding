# Diagnose a Scaled System That Is Slow — full-stack starter

Requires Node.js 20+. The Express API accepts shard samples and the React
dashboard submits an incident snapshot and displays its fleet summary.

```bash
cd backend
npm install
npm start
```

```bash
cd frontend
npm install
npm run dev
```

Core tests need no installed packages: `cd backend && node --test`. The
baseline intentionally fails only the hot-shard regression. The descriptively
named hypothesis-ranking and probe-recommendation APIs remain incomplete.
