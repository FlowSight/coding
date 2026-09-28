# URL request runner full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for submitting batches of URLs.
Parallel execution, bounded concurrency, and error reporting remain incomplete.

```bash
cd backend && python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload
cd ../frontend && npm install && npm run dev
```

The standard-library baseline uses an injected requester, avoids FastAPI and real
network access, and intentionally fails only because deduplication loses first-seen order.
