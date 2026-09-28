
from __future__ import annotations
from dataclasses import dataclass


@dataclass(frozen=True)
class MetricSample:
    shard: str
    latency_ms: float
    requests: int
    errors: int = 0


@dataclass(frozen=True)
class ShardSummary:
    shard: str
    average_latency_ms: float
    requests: int
    errors: int


@dataclass(frozen=True)
class Hypothesis:
    name: str
    score: float
    evidence: tuple[str, ...] = ()


@dataclass(frozen=True)
class Probe:
    name: str
    rationale: str
