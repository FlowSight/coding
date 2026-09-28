
from __future__ import annotations
from dataclasses import dataclass
from enum import Enum


@dataclass(frozen=True)
class DataEvent:
    id: str
    type: str
    payload: dict[str, str] | None


class RejectionReason(Enum):
    MISSING_ID = "missing_id"
    UNSUPPORTED_TYPE = "unsupported_type"
    MISSING_PAYLOAD = "missing_payload"
    DUPLICATE_ID = "duplicate_id"


@dataclass(frozen=True)
class RejectedEvent:
    event: DataEvent
    reason: RejectionReason


@dataclass(frozen=True)
class FilterReport:
    accepted: tuple[DataEvent, ...]
    rejected: tuple[RejectedEvent, ...]


@dataclass(frozen=True)
class StreamResult:
    event: DataEvent
    accepted: bool
    reason: RejectionReason | None = None
