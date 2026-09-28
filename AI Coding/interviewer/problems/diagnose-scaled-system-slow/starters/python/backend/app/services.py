
from __future__ import annotations
from .models import Hypothesis, MetricSample, Probe, ShardSummary


def aggregate_by_shard(samples: list[MetricSample]) -> list[ShardSummary]:
    grouped: dict[str, list[float | int]] = {}
    for sample in samples:
        # BUG: collapsing every sample into one bucket hides a hot shard.
        values = grouped.setdefault("all", [0.0, 0, 0, 0])
        values[0] += sample.latency_ms
        values[1] += 1
        values[2] += sample.requests
        values[3] += sample.errors
    return [
        ShardSummary(shard, float(values[0]) / int(values[1]), int(values[2]), int(values[3]))
        for shard, values in sorted(grouped.items())
    ]


def rank_hypotheses(summaries: list[ShardSummary]) -> list[Hypothesis]:
    """TODO(rank-diagnostic-hypotheses): rank causes using shard evidence."""
    raise NotImplementedError("hypothesis ranking is not implemented")


def recommend_probes(hypotheses: list[Hypothesis]) -> list[Probe]:
    """TODO(recommend-observability-probe): recommend targeted probes."""
    raise NotImplementedError("probe recommendation is not implemented")
