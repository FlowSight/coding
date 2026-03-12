Problem: Virus Spread in a Grid (Rotting Oranges Variant)
You are given an m x n 2D grid grid where each cell is:

0: empty
1: healthy
2: infected
Every minute, the virus spreads from all currently infected cells to their 4-directionally adjacent (up/down/left/right) healthy cells, turning them infected.

Return the minimum number of minutes needed to infect all healthy cells. If it is impossible to infect all healthy cells, return -1. If there are no healthy cells initially, return 0.

Constraints
1 <= m, n <= 200
grid[i][j] ∈ {0,1,2}
Output
Output one integer: the minimum minutes, or -1.
Examples
[[2,1,1],[1,1,0],[0,1,1]] → 4
[[2,1,1],[0,1,1],[1,0,1]] → -1
[[0,2]] → 0
Example
Input
3 3
2 1 1
1 1 0
0 1 1
Output
4