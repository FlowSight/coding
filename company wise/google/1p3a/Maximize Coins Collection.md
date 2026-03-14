How many coins can be collected from a game board? Given a string representing a single row board with a maximum length of 100, containing characters '.', 'T', and 'C', representing empty positions, player's tokens, and coins respectively. The player can move multiple tokens, with each token moving strictly 3 places to the right, and cannot move to the left or for any other number of steps. If the target position is occupied by another token, the move is invalid. Coins can only be collected if a token lands on it, not when passing by. Calculate the maximum number of coins the player can collect.

Example
Input
'...TC.TC.'