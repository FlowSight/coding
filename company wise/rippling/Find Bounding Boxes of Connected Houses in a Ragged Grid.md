Problem: Find Bounding Boxes of Connected Houses in a Ragged Grid
You are given a 2D grid grid representing a map. The grid is ragged: row i may have a different length than other rows.

grid[i][j] == '1' means the cell belongs to a house
grid[i][j] == '*' (or 0) means empty land
House definition: two '1' cells belong to the same house if they are adjacent in 4 directions (up/down/left/right).

Output
For each house, output the bounding rectangle defined by:

the top-left coordinate
the bottom-right coordinate
Coordinates must be formatted as RowLetter + ColumnNumber:

Row is an uppercase letter: row 0 is A, row 1 is B, etc.
Column is 1-based: column 0 is 1, column 1 is 2, etc.
Each house should be printed as:

<topLeft> <bottomRight>
Example:

A2 B3
Input (stdin)
Line 1: integer R (# of rows)
Next R lines: space-separated characters (1 or *), each row may have different length
Output (stdout)
Print K lines (K houses). Order does not matter.

Constraints
1 <= R <= 200
1 <= len(row) <= 200
Total cells sum(len(row)) <= 40000
Samples
Sample 1
Input:

3
* * * * 1 1 1 * *
* 1 1 * *
* * 1 1 * * *
Output (any order):

A5 A7
B2 C4
Sample 2
Input:

2
1 1 1
1
Output:

A1 B3
Sample 3
Input:

4
* *
* * *
* *
* * * *
Output: (no output)

Sample 4
Input:

1
1 * 1 * 1
Output (any order):

A1 A1
A3 A3
A5 A5
Sample 5
Input:

3
1 1 *
* 1 1 1
* * 1
Output:

A1 C3
Example
Input
3
* * * * 1 1 1 * *
* 1 1 * *
* * 1 1 * * *
Output
A5 A7
B2 C4