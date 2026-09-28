
from __future__ import annotations
import unittest

from app.models import MetricSample
from app.services import aggregate_by_shard


class DiagnosticsTests(unittest.TestCase):
    def test_aggregation_preserves_hot_shard(self) -> None:
        summaries = aggregate_by_shard(
            [MetricSample("cold", 10, 100), MetricSample("hot", 500, 100, 7)]
        )
        self.assertEqual(len(summaries), 2)
        self.assertEqual(summaries[1].shard, "hot")
        self.assertEqual(summaries[1].average_latency_ms, 500)


if __name__ == "__main__":
    unittest.main()
