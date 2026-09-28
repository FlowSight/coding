# URL request execution starter

The sequential path still deduplicates requests and loses input order. Parallel
and bounded-concurrency/error-policy APIs remain incomplete.

```bash
cd backend && mvn spring-boot:run
cd frontend && npm install && npm run dev
```

Run `cd backend && mvn test`; the baseline backend test intentionally fails once.
