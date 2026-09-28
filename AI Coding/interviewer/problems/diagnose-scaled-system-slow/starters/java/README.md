# Scaled system diagnostics starter

This full-stack seed keeps the traffic-weighted aggregation bug and leaves the
hypothesis-ranking and probe-recommendation follow-ups incomplete.

```bash
cd backend && mvn spring-boot:run
cd frontend && npm install && npm run dev
```

Run backend tests with `cd backend && mvn test`. The baseline backend test
intentionally fails once because the seeded bug masks a low-volume hot shard.
