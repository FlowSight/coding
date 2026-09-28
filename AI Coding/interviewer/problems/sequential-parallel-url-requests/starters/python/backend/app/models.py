
from __future__ import annotations
from dataclasses import dataclass
from enum import Enum


@dataclass(frozen=True)
class Response:
    status_code: int
    body: bytes


@dataclass(frozen=True)
class Result:
    url: str
    response: Response | None = None
    error: Exception | None = None


class Mode(Enum):
    SEQUENTIAL = "sequential"
    PARALLEL = "parallel"


@dataclass(frozen=True)
class Options:
    mode: Mode = Mode.SEQUENTIAL
    max_concurrency: int = 1


@dataclass(frozen=True)
class ErrorReport:
    url: str
    error: Exception


@dataclass(frozen=True)
class Report:
    results: tuple[Result, ...]
    errors: tuple[ErrorReport, ...] = ()
