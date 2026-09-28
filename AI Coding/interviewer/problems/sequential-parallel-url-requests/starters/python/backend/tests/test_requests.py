
from __future__ import annotations
import unittest

from app.models import Response
from app.services import request_sequential


class RecordingRequester:
    def __init__(self) -> None:
        self.calls: list[str] = []

    def request(self, url: str) -> Response:
        self.calls.append(url)
        return Response(200, url.encode())


class RequestTests(unittest.TestCase):
    def test_sequential_deduplicates_in_first_seen_order(self) -> None:
        requester = RecordingRequester()
        results = request_sequential(
            ["https://b.example", "https://a.example", "https://b.example"], requester
        )
        expected = ["https://b.example", "https://a.example"]
        self.assertEqual([result.url for result in results], expected)
        self.assertEqual(requester.calls, expected)


if __name__ == "__main__":
    unittest.main()
