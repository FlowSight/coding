
from __future__ import annotations
from fastapi import FastAPI

from .routes import router

app = FastAPI(title="Event Validation API")
app.include_router(router)
