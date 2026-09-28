# Sliding-window rate limiter starter

The exact-window-boundary defect is preserved. Per-key limiting and stale-key
cleanup APIs remain incomplete.

```bash
cd backend && mvn spring-boot:run
cd frontend && npm install && npm run dev
```

Run `cd backend && mvn test`; the baseline backend test intentionally fails once.
