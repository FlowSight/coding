You are given a 1D board represented by a string s of length n, containing multiple tokens and coins.

Each token can move only to the right.
Each move must be exactly 3 steps to the right (from index i to i+3), with no stopping in between.
If a token lands on a cell containing a coin, it collects the coin (the coin is removed).
A token may perform any number of moves as long as it stays within the board (i.e., i+3 < n).
Compute the maximum number of coins that can be collected with an optimal strategy.

Input (suggested): one line string s.

Output: an integer, the maximum number of coins collectable.

Constraints (suggested): 1 <= n <= 2e5.

Example:

Input: T..C..C.TC
Output: 2
The example is illustrative; the exact character set (e.g., T token, C coin, . empty) should follow the original prompt.

Example
Input
T..C..C.TC
Output
2