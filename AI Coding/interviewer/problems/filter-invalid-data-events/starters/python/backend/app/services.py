
from __future__ import annotations
from collections.abc import Iterable, Iterator

from .models import DataEvent, FilterReport, StreamResult


def filter_valid_events(events: list[DataEvent]) -> list[DataEvent]:
    by_id: dict[str, DataEvent] = {}
    for event in events:
        if not event.id:
            continue
        # BUG: validation is incomplete, later duplicates win, and IDs are sorted.
        by_id[event.id] = event
    return [by_id[event_id] for event_id in sorted(by_id)]


def filter_events(events: list[DataEvent]) -> FilterReport:
    """TODO(report-rejection-details): report one deterministic rejection reason."""
    raise NotImplementedError("rejection reporting is not implemented")


def filter_stream(events: Iterable[DataEvent]) -> Iterator[StreamResult]:
    """TODO(stream-validated-events): validate and deduplicate lazily."""
    raise NotImplementedError("stream filtering is not implemented")
