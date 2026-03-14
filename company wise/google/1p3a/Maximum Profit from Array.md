Given a 1D array of positive integers. Your initial position is at index 0. At index i, you can choose to:

Take the profit at arr[i] and jump to index (i + 1 + arr[i]).
Not take the profit and move to index (i + 1).
Calculate the maximum profit you can achieve.

Test Case
Input: [3, 2, 5, 0, 0, 1]

Output: 8

Constraints
The length of the array is between 1 to 10000, with integer elements.
Follow Up
The numbers in the array can also be negative.

Example
Input
[3, 2, 5, 0, 0, 1]