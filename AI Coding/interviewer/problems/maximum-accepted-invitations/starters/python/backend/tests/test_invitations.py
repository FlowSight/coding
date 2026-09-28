
from __future__ import annotations
import unittest

from app.services import maximum_invitations


class MaximumInvitationsTests(unittest.TestCase):
    def test_empty(self) -> None:
        self.assertEqual(maximum_invitations([]), 0)

    def test_single_pair(self) -> None:
        self.assertEqual(maximum_invitations([[1]]), 1)

    def test_reroutes_an_earlier_match(self) -> None:
        self.assertEqual(maximum_invitations([[1, 1], [1, 0]]), 2)


if __name__ == "__main__":
    unittest.main()
