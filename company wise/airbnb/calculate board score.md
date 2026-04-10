You are given a 2D board board of size R x C, where each cell contains a character representing a piece/type (e.g., 'A', 'B', '.'; the character set is not restricted).

The scoring rule is:

For every cell (i, j), starting from that cell, look to the right and down and compute the length of the contiguous run of the same character as board[i][j] (adjacent cells only, no gaps).
If the run length in a direction is L, that direction contributes L to the total score.
The board score is the sum of contributions from all cells in both directions (right and down).
Implement a function to compute and return the total score.

Input format (standardized)
First line: two integers R C
Next R lines: a string of length C describing each row
Output format
Print one integer: the board total score
Constraints
1 <= R, C <= 2000 (an O(RC) or near-linear solution is expected)
Board characters are printable ASCII
Sample tests
Test 1
Input:

2 2
AA
AA
Output:

12
Test 2
Input:

1 4
ABBB
Output:

8
Test 3
Input:

3 3
ABC
DEF
GHI
Output:

18
Test 4
Input:

3 5
AABBA
AABBA
CCDDD
Output:

52
Test 5
Input:

2 3
...
..X
Output:

20