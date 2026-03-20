You are given an m x n grid where each cell contains an integer. Given a start cell (r1, c1) and a target value t, determine if there exists a path from (r1, c1) to any cell that contains t. The path must only move through cells that have value k (excluding the start and end cells).

Input:

A two-dimensional list grid representing the grid, where grid[i][j] is the integer value of the cell at row i and column j.
An integer r1 and c1 representing the start cell's row and column numbers.
An integer k representing the cell value that the path must pass through.
An integer t representing the target value.
Output:

A boolean indicating whether such a path exists.
Example Test Case:

Input: grid = [[1,2,3],[4,5,6],[7,8,9]], r1 = 0, c1 = 0, k = 5, t = 9
Output: True
Constraints:

Total number of rows and columns in the grid does not exceed 10,000.
0 <= grid[i][j], k, t <= 1000.
Example
Input
3 3
1 2 3
4 5 6
7 8 9
0 0
5
9