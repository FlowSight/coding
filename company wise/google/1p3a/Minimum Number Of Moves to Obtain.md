Things begin with an array filled with N zeros, and, we, as a team, want to obtain an array A.

In one move, we can choose an arbitrary inverval and increase all the elements within that inverval by 1. For example:::

We can transform [0, 0, 0, 0, 0] into [0, 1, 1, 1, 0] in a single move.

BUT! We need three moves to obtain [1, 0, 1, 2, 2]. One possible sequence of moves is: [0, 0, 0, 0 , 0] -> [0, 0, 1, 1, 1] -> [0, 0, 1, 2, 2] -> [1, 0, 1, 2, 2], where -> denotes a single move.

What is the minimum number of moves needed to obtain A? Starting from a zero-filled array?

Given an array A of length N, returns an integer that represents the minimum number of moves needed to transform a zero-filled array into A

Constraints:

N is an integer within the range [1..100,000]
each element of array A is an integer within the range [0..1,000,000,000]
we guarantee that the answer will not exceed 1,000,000,000
Example
Input
A = [2, 1, 3]
Output
4