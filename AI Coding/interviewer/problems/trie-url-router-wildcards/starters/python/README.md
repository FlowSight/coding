# Trie URL router full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for editing and testing trie
routes. Route removal and concurrent updates remain intentionally incomplete.

```bash
cd backend && python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload
cd ../frontend && npm install && npm run dev
```

The standard-library baseline avoids FastAPI and intentionally fails only because
matching does not backtrack from a static dead end to a wildcard sibling.
