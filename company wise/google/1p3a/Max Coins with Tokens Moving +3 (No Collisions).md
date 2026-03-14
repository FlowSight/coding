Problem
A single-player board game is described by a string board of length N (indices 0..N-1). Each position is one of:

'.': empty
'T': a player token (there may be multiple tokens)
'C': a coin
A coin is collected when a token is placed on its position; each coin can be collected at most once.

Move rule
In one turn, the player may choose one token and move it exactly 3 positions to the right:

From index i to i+3 (the token does not stop on intermediate cells; they have no effect).
A token may be moved multiple times.
The move is not allowed if the destination cell i+3 is already occupied by another token (tokens cannot overlap).
The move must stay within the board: it is only possible if i+3 < N.
Goal
Return the maximum number of coins that can be collected by performing an optimal sequence of moves.

Function signature
def solution(board: str) -> int:
    ...
Constraints
1 <= N <= 100
board consists only of '.', 'T', and 'C'
Examples
board = "TT.T.CCCCC" => 3
board = "T...CCCC" => 1
board = "C..TT.CT.C" => 2
Example
Input
TT.T.CCCCC
Output
3