# Data event validation starter

The seed keeps the validation, duplicate-selection, and stable-ordering defects.
Detailed rejection reporting and streaming APIs remain deliberately incomplete.

```bash
cd backend && mvn spring-boot:run
cd frontend && npm install && npm run dev
```

Run `cd backend && mvn test`; the baseline backend test intentionally fails once.
