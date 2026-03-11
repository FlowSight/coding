There is a maze in HackerPlay where children play for recreation.

The maze is represented as an n * m grid of cells, where each cell is either empty (denoted by 0), or contains an obstacle (denoted by 1). HackerMan is currently standing at cell (0, 0) and wishes to reach the cell (n - 1, m - 1).

For a jump parameter denoted by k, in one move, HackerMan can move to any of the following cells:

(i + x, j) where 1 ≤ x ≤ k provided cell (i + x, j) lies in the maze and there are no cells containing obstacles in the range (i, j) → (i + 1, j) → ... → (i + x, j).
(i - x, j) where 1 ≤ x ≤ k provided cell (i - x, j) lies in the maze and there are no cells containing obstacles in the range (i, j) → (i - 1, j) → ... → (i - x, j).
(i, j + x) where 1 ≤ x ≤ k provided cell (i, j + x) lies in the maze and there are no cells containing obstacles in the range (i, j) → (i, j + 1) → ... → (i, j + x).
(i, j - x) where 1 ≤ x ≤ k provided cell (i, j - x) lies in the maze and there are no cells containing obstacles in the range (i, j) → (i, j - 1) → ... → (i, j - x).
Find the minimum number of moves in which HackerMan can reach the cell (n - 1, m - 1) starting from (0, 0), or -1 if it is impossible to reach that cell.

Function Description

Complete the function getMinimumMoves in the editor below.

getMinimumMoves has the following parameters:

int maze[n][m]: the maze in HackerPlay where HackerMan is standing
int k: the maximum distance HackerMan can traverse in one move
Returns

int: the minimum number of moves in which HackerMan can reach the destination cell (n - 1, m - 1)

Constraints

1 ≤ n ≤ 100
1 ≤ m ≤ 100
1 ≤ k ≤ 100
Each cell of the grid contains values either 0 or 1.
Constraints: :)

Example
Input
maze = [[0, 0], [1, 0]]
k = 2
Output
2