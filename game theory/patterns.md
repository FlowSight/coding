1. Sprague-grundy: The core idea: a game is just a number

   1. grundy(n) = mex{grundy(m) where m is reachable from n in one legal move}, mex = smallest non-neg int that not in list, grundy(0) = 0, grundy(1) = mex(grundy(0)) = 1,
   2. If 2 (or n) independent piles are there i.e. u pick a pile, then remove square no of stones from that -> terminates when both pile is 0 , you lose
   3. e.g. piles(1,1) = grundy(1,1), u go first (1,0), other goes second (0,0) , u lose
   4. Hence XOR of all grundy should be nonzero, for next move player to win
   5. Every impartial game (both players have the exact same available moves at any position — this is key, it's not for games like chess where players have different pieces) is equivalent to a Nim-pile of some size, called its Grundy number (or "nimber").
   6. Use ONLY when there are independent sub-games combined by "pick one, move in it" — nothing to XOR (single shared running total, no independent piles) means this machinery buys nothing (see LC 464 below, where it collapses to plain win/lose bitmask DP)
2.
