Number of Islands (Union-Find preferred)
You are given a 2D grid grid consisting of 0s and 1s, where 1 represents land and 0 represents water. Two land cells are in the same island if they are adjacent horizontally or vertically (4-directionally).

Return the number of islands in the grid.

Input (stdin)
The first line contains two integers m n, the number of rows and columns.
The next m lines each contain a string of length n made of characters 0/1.
Output (stdout)
Print one integer: the number of islands.
Constraints
1 <= m, n <= 300 (typical interview scale; may vary)
Example
Input:

4 5
11110
11010
11000
00000
Output:

1
Requirement
Union-Find / DSU solution is preferred.
Example
Input
4 5
11110
11010
11000
00000
Output
1