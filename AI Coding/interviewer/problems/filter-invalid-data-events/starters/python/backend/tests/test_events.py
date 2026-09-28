
from __future__ import annotations
import unittest

from app.models import DataEvent
from app.services import filter_valid_events


class EventTests(unittest.TestCase):
    def test_validates_deduplicates_and_preserves_order(self) -> None:
        first_b = DataEvent("b", "created", {"version": "first"})
        event_a = DataEvent("a", "updated", {"version": "one"})
        second_b = DataEvent("b", "updated", {"version": "second"})
        invalid = DataEvent("bad", "deleted", {"version": "one"})
        self.assertEqual(
            filter_valid_events([first_b, event_a, second_b, invalid]),
            [first_b, event_a],
        )


if __name__ == "__main__":
    unittest.main()
