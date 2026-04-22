Problem: Longest Subarray with At Most Two Distinct Values
You are given an integer array fruits where fruits[i] is the fruit type on the i-th tree. You pick fruits from a contiguous segment of trees.

You have two baskets:

Each basket can hold only one fruit type
Each basket has unlimited capacity
Return the maximum number of fruits you can pick (i.e., the maximum length of a contiguous subarray) such that the chosen subarray contains at most two distinct numbers.

Input/Output
Input:
Line 1: integer n
Line 2: n integers for array fruits
Output:
One integer: the maximum valid length
Constraints
1 <= n <= 2 * 10^5
0 <= fruits[i] <= 10^9
Examples
input:
3
1 2 1
output:
3
input:
4
0 1 2 2
output:
3
input:
5
1 2 3 2 2
output:
4
input:
10
1 1 1 1 1 1 1 1 1 1
output:
10
input:
8
3 3 3 1 2 1 1 2
output:
5
Example
Input
3
1 2 1
Output
3