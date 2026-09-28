
from __future__ import annotations
import unittest

from app.models import Match
from app.services import Router


class RouterTests(unittest.TestCase):
    def test_backtracks_from_static_dead_end_to_wildcard(self) -> None:
        router = Router()
        router.insert("/:kind/:id", "show")
        router.insert("/users/new/settings", "settings")
        self.assertEqual(
            router.match("/users/new"),
            Match("show", {"kind": "users", "id": "new"}),
        )


if __name__ == "__main__":
    unittest.main()
