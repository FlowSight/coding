
from __future__ import annotations
import unittest
from datetime import datetime, timedelta, timezone

from app.services import Limiter


class LimiterTests(unittest.TestCase):
    def test_expires_request_at_exact_window_boundary(self) -> None:
        limiter = Limiter(1, timedelta(minutes=1))
        start = datetime(2026, 1, 1, tzinfo=timezone.utc)
        self.assertTrue(limiter.allow(start))
        self.assertTrue(limiter.allow(start + timedelta(minutes=1)))


if __name__ == "__main__":
    unittest.main()
