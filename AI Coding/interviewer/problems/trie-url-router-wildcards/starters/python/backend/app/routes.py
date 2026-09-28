
from __future__ import annotations
from fastapi import APIRouter
from pydantic import BaseModel

from .services import Router

router = APIRouter(prefix="/api/router", tags=["router"])
trie = Router()


class RouteInput(BaseModel):
    pattern: str
    handler: str


@router.post("/routes")
def add_route(body: RouteInput) -> dict[str, str]:
    trie.insert(body.pattern, body.handler)
    return {"status": "created"}


@router.get("/match")
def match_route(path: str) -> dict[str, object] | None:
    match = trie.match(path)
    return {"handler": match.handler, "params": match.params} if match else None
