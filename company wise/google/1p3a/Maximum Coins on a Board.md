You have a one-dimensional board where each cell can be empty, occupied by a piece, or occupied by a coin.

If a piece moves onto an empty cell, nothing happens;
If it moves onto a coin cell, the player collects that coin;
No two pieces can overlap.
You can take as many rounds as needed until no pieces can be moved further. What's the maximum number of coins you can collect?

Input
A character array representing the board state, for example: ['.', 'P', 'C', '.', 'C', '.', 'P', '.', 'C'], where '.' means empty, 'P' means piece, and 'C' means coin.
Output
An integer indicating the maximum number of coins that can be collected.
Example
Input: ['.', 'P', 'C', '.', 'C', '.', 'P', '.', 'C'] Output: 2

Explanation
The first piece can move 3 times to reach the first coin cell. The second piece can move 1 time to reach the second coin cell.

Constraints
Board length does not exceed 1000 and contains at least one piece and one coin.
Example
Input
7
.P.C..P..C