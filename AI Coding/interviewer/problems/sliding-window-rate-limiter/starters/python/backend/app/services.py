
from __future__ import annotations
from collections import deque
from datetime import datetime, timedelta


class Limiter:
    def __init__(self, limit: int, window: timedelta) -> None:
        if limit <= 0 or window <= timedelta(0):
            raise ValueError("limit and window must be positive")
        self._limit = limit
        self._window = window
        self._timestamps: deque[datetime] = deque()

    def allow(self, now: datetime) -> bool:
        cutoff = now - self._window
        # BUG: the exact cutoff is outside the active interval.
        while self._timestamps and self._timestamps[0] < cutoff:
            self._timestamps.popleft()
        if len(self._timestamps) >= self._limit:
            return False
        self._timestamps.append(now)
        return True


class KeyedLimiter:
    def __init__(self, limit: int, window: timedelta) -> None:
        if limit <= 0 or window <= timedelta(0):
            raise ValueError("limit and window must be positive")
        self._limit = limit
        self._window = window
        # TODO(per-key-rate-limits): initialize independent windows for each key.

    def allow(self, key: str, now: datetime) -> bool:
        """TODO(per-key-rate-limits): enforce limits independently by key."""
        raise NotImplementedError("per-key limiting is not implemented")

    def cleanup(self, now: datetime) -> int:
        """TODO(stale-key-cleanup): safely remove idle keys."""
        raise NotImplementedError("cleanup and concurrency are not implemented")
