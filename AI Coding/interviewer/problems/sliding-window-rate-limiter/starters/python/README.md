# Rate limiter full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for exploring a sliding-window
limiter. Per-key limits and idle-key cleanup remain intentionally incomplete.

```bash
cd backend && python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload
cd ../frontend && npm install && npm run dev
```

The standard-library baseline avoids FastAPI and intentionally fails only because
a request exactly on the window boundary is retained.
