
from __future__ import annotations
from dataclasses import dataclass, field


@dataclass
class Node:
    static: dict[str, "Node"] = field(default_factory=dict)
    wildcard: "Node | None" = None
    wildcard_name: str = ""
    handler: str | None = None


@dataclass(frozen=True)
class Match:
    handler: str
    params: dict[str, str]
