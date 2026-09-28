
from __future__ import annotations
from .models import Match, Node


class Router:
    def __init__(self) -> None:
        self._root = Node()

    def insert(self, pattern: str, handler: str) -> None:
        current = self._root
        for segment in _segments(pattern):
            if segment.startswith(":"):
                if current.wildcard is None:
                    current.wildcard = Node()
                current.wildcard_name = segment[1:]
                current = current.wildcard
            else:
                current = current.static.setdefault(segment, Node())
        current.handler = handler

    def match(self, path: str) -> Match | None:
        return self._match(self._root, _segments(path), 0, {})

    def _match(self, current: Node, path: list[str], index: int, params: dict[str, str]) -> Match | None:
        if index == len(path):
            return Match(current.handler, params) if current.handler is not None else None
        static = current.static.get(path[index])
        if static is not None:
            # BUG: a static dead end must backtrack to the wildcard sibling.
            return self._match(static, path, index + 1, params)
        if current.wildcard is not None:
            captured = dict(params)
            captured[current.wildcard_name] = path[index]
            return self._match(current.wildcard, path, index + 1, captured)
        return None

    def remove(self, pattern: str) -> bool:
        """TODO(route-removal-trie-pruning): remove a route and prune nodes."""
        raise NotImplementedError("route removal is not implemented")

    # TODO(concurrent-route-updates): make all operations safe for concurrent callers.


def _segments(path: str) -> list[str]:
    return [segment for segment in path.strip("/").split("/") if segment]
