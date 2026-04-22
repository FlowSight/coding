Given an integer array nums, traverse it from left to right and compute the sum of all positive adjacent differences:

[ \text{ans} = \sum_{i=1}^{n-1} \max(0, nums[i] - nums[i-1]) ]

Output ans.

Common equivalent interpretation: if nums[i] is a stock price on day i, then ans is the maximum profit with unlimited transactions (cannot hold multiple positions at once).

Input (stdin)
Line 1: integer n
Line 2: n integers, the array nums
Output (stdout)
One integer ans
Constraints
1 <= n <= 2e5
-1e9 <= nums[i] <= 1e9
Examples / Tests
Test 1
Input:

6
7 1 5 3 6 4
Output:

7
Test 2
Input:

5
1 2 3 4 5
Output:

4
Test 3
Input:

5
5 4 3 2 1
Output:

0
Test 4
Input:

1
10
Output:

0
Test 5
Input:

6
3 3 5 0 0 3
Output:

5
Example
Input
6
7 1 5 3 6 4
Output
7