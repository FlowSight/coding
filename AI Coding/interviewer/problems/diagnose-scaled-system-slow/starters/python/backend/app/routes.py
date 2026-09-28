
from __future__ import annotations
from fastapi import APIRouter
from pydantic import BaseModel

from .models import MetricSample
from .services import aggregate_by_shard

router = APIRouter(prefix="/api/diagnostics", tags=["diagnostics"])


class SampleInput(BaseModel):
    shard: str
    latency_ms: float
    requests: int
    errors: int = 0


@router.post("/aggregate")
def aggregate(samples: list[SampleInput]) -> list[dict[str, object]]:
    summaries = aggregate_by_shard([MetricSample(**sample.model_dump()) for sample in samples])
    return [summary.__dict__ for summary in summaries]
