
from __future__ import annotations
from fastapi import FastAPI

from .routes import router

app = FastAPI(title="Sliding Window Limiter API")
app.include_router(router)
