# Scaled-system diagnostics full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for comparing shard metrics.
Hypothesis ranking and observability probe recommendations remain incomplete.

```bash
cd backend && python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload
cd ../frontend && npm install && npm run dev
```

The standard-library baseline avoids FastAPI and intentionally fails only because
the seeded aggregation bug collapses all shards and hides the hot shard.
