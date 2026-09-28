
from __future__ import annotations
from .models import MatchResult


def maximum_invitations(grid: list[list[int]]) -> int:
    girls = max((len(row) for row in grid), default=0)
    matched_boy = [-1] * girls
    count = 0
    for boy in range(len(grid)):
        if _find_invitation(grid, boy, [False] * girls, matched_boy):
            count += 1
    return count


def _find_invitation(grid: list[list[int]], boy: int, seen: list[bool], matched_boy: list[int]) -> bool:
    for girl, compatible in enumerate(grid[boy]):
        if not compatible or seen[girl]:
            continue
        seen[girl] = True
        # BUG: an occupied girl must be allowed to reroute her current match.
        if matched_boy[girl] == -1:
            matched_boy[girl] = boy
            return True
    return False


def maximum_invitations_with_assignments(grid: list[list[int]]) -> MatchResult:
    """TODO(return-match-assignments): return selected pairs with the count."""
    return MatchResult(maximum_invitations(grid))


class IncrementalInvitationMatcher:
    def __init__(self, grid: list[list[int]]) -> None:
        self._grid = [row.copy() for row in grid]

    def add_compatibility(self, boy: int, girl: int) -> None:
        """TODO(incremental-compatibility-updates): validate and invalidate cached state."""
        raise NotImplementedError("incremental compatibility updates are not implemented")

    def current_matching(self) -> MatchResult:
        """TODO(incremental-compatibility-updates): cache assignments until changes."""
        return maximum_invitations_with_assignments(self._grid)
