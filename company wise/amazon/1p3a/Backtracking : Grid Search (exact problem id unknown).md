Coding: Grid Search / Backtracking (exact LC id unknown; referred as “LC 药翎耀耀”)
Given an m x n grid grid of non-negative integers (each cell is a “reward”), you may start from any cell and move up/down/left/right to adjacent cells.

Constraint: each cell can be visited at most once in a path.
Goal: compute the maximum total reward (sum of values along the path).
Input (stdin)
First line: two integers m n
Next m lines: n integers each for grid[i][j]
Output (stdout)
A single integer: the maximum achievable reward
Constraints
1 <= m, n <= 15
0 <= grid[i][j] <= 100
Example
Input:

3 3
0 6 0
5 8 7
0 9 0
Output:

24
This is highly similar to LeetCode 1219. Path with Maximum Gold.

Example
Input
3 3
0 6 0
5 8 7
0 9 0
Output
24