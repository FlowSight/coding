You are given an integer array tiles of length 14 representing a Mahjong hand (each integer is a tile type; equal integers mean the same tile).

Determine whether the hand is a winning hand under the simplified rule:

The 14 tiles can be partitioned into 4 melds + 1 pair.
Each meld is either:
Triplet: three identical tiles [x, x, x], or
Sequence: three consecutive tiles [x, x+1, x+2].
The pair is two identical tiles [y, y].
Return true if the hand can win, otherwise false.

Constraints:

len(tiles) = 14
Tile values are positive integers (tile ids)
Each tile type appears at most 4 times
Examples:

Input: [1,1,1, 2,3,4, 2,3,4, 5,6,7, 8,8] -> Output: true
Input: [1,1,1, 2,2,2, 3,3,3, 4,4,5,5,6] -> Output: false
Example
Input
1 1 1 2 3 4 2 3 4 5 6 7 8 8
Output
true