Problem: Sum of all “good subarrays” where adjacent difference is ±1
Given an integer array nums of length n. A subarray is defined as good if and only if the absolute difference between every pair of adjacent elements in the subarray is exactly 1. That is, for all l < i ≤ r:

|nums[i] - nums[i-1]| = 1
Compute the total sum of elements over all good subarrays (sum each good subarray, then sum over all such subarrays).

Input (stdin)
Line 1: integer n
Line 2: n integers representing nums
Output (stdout)
One integer: the total sum over all good subarrays
Constraints
1 ≤ n ≤ 2 * 10^5
-10^9 ≤ nums[i] ≤ 10^9
Required time complexity: O(n)
Example
Input:

5
3 5 6 7 6
Output:

69
Explanation: Good subarrays include all singletons and those with adjacent diff ±1, e.g. [5,6], [6,7], [7,6], [5,6,7].

Example
Input
5
3 5 6 7 6
Output
69