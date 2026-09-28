# Maximum invitations full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for testing compatibility
matrices. Assignment reporting and incremental updates remain intentionally incomplete.

```bash
cd backend && python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload
cd ../frontend && npm install && npm run dev
```

The standard-library baseline avoids FastAPI and intentionally fails only on the
augmenting-path rerouting case.
