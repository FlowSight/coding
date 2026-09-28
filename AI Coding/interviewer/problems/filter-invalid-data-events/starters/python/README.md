# Event validation full-stack starter

Python 3.11 FastAPI backend and React/Vite frontend for validating data events.
Detailed rejection reports and streaming validation remain intentionally incomplete.

```bash
cd backend
python3.11 -m unittest -v
python3.11 -m pip install -r requirements.txt
uvicorn app.main:app --reload

cd ../frontend
npm install
npm run dev
```

The standard-library baseline test does not import FastAPI. It intentionally fails
only because validation, first-seen deduplication, and stable ordering are incorrect.
