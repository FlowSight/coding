Problem
You are given an m × n grid grid representing a roof:

grid[i][j] = 1 means the cell is intact.
grid[i][j] = 0 means the cell is a hole that must be patched.
You can use two types of boards (each board must cover a contiguous full line):

Horizontal board of size 1 × n covering an entire row.
Vertical board of size m × 1 covering an entire column.
A board may cover intact cells as well, but every hole cell (0) must be covered by at least one chosen board.

Compute the minimum number of boards needed to cover all holes.

Input (stdin)
Line 1: m n
Next m lines: n values (0/1) for the grid
Output (stdout)
One integer: the minimum number of boards
Constraints
1 <= m, n <= 200
grid[i][j] ∈ {0,1}
Example
Input
2 3
1 0 1
1 1 1
Output
1