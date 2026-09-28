
from __future__ import annotations
from fastapi import APIRouter
from pydantic import BaseModel

from .models import DataEvent
from .services import filter_valid_events

router = APIRouter(prefix="/api/events", tags=["events"])


class EventInput(BaseModel):
    id: str
    type: str
    payload: dict[str, str] | None = None


@router.post("/filter")
def filter_events_route(events: list[EventInput]) -> list[dict[str, object]]:
    accepted = filter_valid_events(
        [DataEvent(event.id, event.type, event.payload) for event in events]
    )
    return [
        {"id": event.id, "type": event.type, "payload": event.payload}
        for event in accepted
    ]
