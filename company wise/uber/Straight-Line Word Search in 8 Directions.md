Given an R x C 2D character grid board and a string word, determine whether word exists in the grid.

Different from the classic Word Search, the rules are:

You may start from any cell.
You may move in 8 directions: up, down, left, right, and the four diagonals.
Once you choose a start cell and a direction, you must keep moving in that same straight line to match each next character of word — no turning.
If you go out of bounds or a character mismatches, that (start, direction) attempt fails.
Output whether there exists at least one straight-line path that matches word.

I/O Format
Input:
First line: two integers R C
Next R lines: each a string of length C
Last line: the string word
Output:
True or False
Constraints
1 <= R, C <= 200
1 <= len(word) <= max(R, C)
Sample Tests
Input:

3 4
ABCE
SFCS
ADEE
ABCC
Output:

True
Input:

3 4
ABCE
SFCS
ADEE
SEE
Output:

True
Input:

3 4
ABCE
SFCS
ADEE
ABCB
Output:

False
Input:

1 5
ABCDE
CDE
Output:

True
Input:

2 2
AA
AA
AAA
Output:

False
Example
Input
3 4
ABCE
SFCS
ADEE
ABCC
Output
True