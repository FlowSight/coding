
from __future__ import annotations
from urllib.request import urlopen

from fastapi import APIRouter
from pydantic import BaseModel

from .models import Response
from .services import request_sequential

router = APIRouter(prefix="/api/requests", tags=["requests"])


class UrlBatch(BaseModel):
    urls: list[str]


class HttpRequester:
    def request(self, url: str) -> Response:
        with urlopen(url, timeout=5) as response:
            return Response(response.status, response.read())


@router.post("/run")
def run_batch(batch: UrlBatch) -> list[dict[str, object]]:
    return [
        {"url": result.url, "status_code": result.response.status_code if result.response else None,
         "error": str(result.error) if result.error else None}
        for result in request_sequential(batch.urls, HttpRequester())
    ]
