
from __future__ import annotations
from fastapi import FastAPI

from .routes import router

app = FastAPI(title="Scaled System Diagnostics API")
app.include_router(router)
