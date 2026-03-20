You're working on a data storage system that represents information in a binary grid. For error correction and symmetry, every row and column must be a palindrome.

Additionally, due to hardware constraints, the total number of 1s must be divisible by 4.

You're allowed to flip any bits (0 -> 1). Return the minimum number of flips needed to make the grid valid.

Example
Input
grid = [[1, 0, 1], [0, 1, 0], [1, 0, 0]]
Output
4