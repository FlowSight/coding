
from __future__ import annotations
from fastapi import FastAPI

from .routes import router

app = FastAPI(title="URL Request Runner API")
app.include_router(router)
