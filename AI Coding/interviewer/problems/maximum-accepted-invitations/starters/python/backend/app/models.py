
from __future__ import annotations
from dataclasses import dataclass


@dataclass(frozen=True)
class Assignment:
    boy: int
    girl: int


@dataclass(frozen=True)
class MatchResult:
    count: int
    assignments: tuple[Assignment, ...] = ()
