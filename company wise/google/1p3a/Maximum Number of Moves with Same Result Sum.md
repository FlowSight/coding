You are given an array A consisting of N numbers. In one move you can delete either the first two, the last two, or the first and last elements of A. No move can be performed if the length of A is smaller than 2. The result of each move is the sum of the deleted elements.

Write a function: class Solution { public int solution(int[] A); }

that, given an array A of N integers, returns the maximum number of moves that can be performed on A, such that all performed moves have the same result.

Constraints: N/A

Example
Input
A = [3, 1, 5, 3, 3, 4, 2]
Output
3