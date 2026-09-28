
from __future__ import annotations
from typing import Protocol

from .models import Options, Report, Response, Result


class Requester(Protocol):
    def request(self, url: str) -> Response: ...


def request_sequential(urls: list[str], requester: Requester) -> list[Result]:
    # BUG: sorting a set loses required first-seen order.
    ordered = sorted(set(urls))
    results: list[Result] = []
    for url in ordered:
        try:
            results.append(Result(url, response=requester.request(url)))
        except Exception as error:
            results.append(Result(url, error=error))
    return results


def request_all(urls: list[str], requester: Requester, options: Options = Options()) -> Report:
    """TODO(parallel-fetching/bounded-concurrency): implement parallel mode and reports."""
    return Report(tuple(request_sequential(urls, requester)))
