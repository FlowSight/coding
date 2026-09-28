
from __future__ import annotations
from fastapi import APIRouter
from pydantic import BaseModel

from .services import maximum_invitations

router = APIRouter(prefix="/api/invitations", tags=["invitations"])


class CompatibilityInput(BaseModel):
    grid: list[list[int]]


@router.post("/maximum")
def maximum(body: CompatibilityInput) -> dict[str, int]:
    return {"count": maximum_invitations(body.grid)}
