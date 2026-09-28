
from __future__ import annotations
from fastapi import FastAPI

from .routes import router

app = FastAPI(title="Trie URL Router API")
app.include_router(router)
