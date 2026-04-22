You are given an integer array stocksProfit representing possible profits from different stock trades (values may be negative, zero, or positive), and an integer target.

Count the number of distinct value pairs (a, b) such that:

a + b = target
a and b come from two different indices in the array
An element cannot pair with itself, unless the value appears at least twice in the array (so (v, v) is allowed only when there are two occurrences)
Count distinct pairs only: pairs with the same values (regardless of indices) are counted once.
Return the number of such distinct pairs.

Input format

Line 1: integer n
Line 2: n integers for stocksProfit
Line 3: integer target
Output format

One integer: the number of distinct pairs.
Constraints (typical OA)

1 <= n <= 2e5
-1e9 <= stocksProfit[i] <= 1e9
-1e9 <= target <= 1e9
Example
Input
6
1 3 2 2 4 0
4
Output
3