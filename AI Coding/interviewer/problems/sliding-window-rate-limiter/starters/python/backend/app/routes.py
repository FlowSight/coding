
from __future__ import annotations
from datetime import datetime, timedelta, timezone

from fastapi import APIRouter
from pydantic import BaseModel

from .services import Limiter

router = APIRouter(prefix="/api/limiter", tags=["limiter"])
limiter = Limiter(3, timedelta(minutes=1))


class Attempt(BaseModel):
    timestamp: datetime | None = None


@router.post("/attempt")
def attempt(body: Attempt) -> dict[str, object]:
    now = body.timestamp or datetime.now(timezone.utc)
    return {"allowed": limiter.allow(now), "evaluated_at": now}
