Given an integer array nums and an integer target, find two distinct indices i != j such that nums[i] + nums[j] == target, and return the two indices (any order).

If no such pair exists, return an empty array.

Requirement: aim for better than O(n^2) time.

Input Format
Line 1: integer n
Line 2: n integers for array nums
Line 3: integer target
Output Format
If exists: print two indices separated by a space
Otherwise: print an empty line
Constraints
0 <= n <= 2 * 10^5
-10^9 <= nums[i], target <= 10^9
Tests
Input:

4
2 7 11 15
9
Output:

0 1
Input:

3
3 2 4
6
Output:

1 2
Input:

2
3 3
6
Output:

0 1
Input:

5
1 2 3 4 5
10
Output:

Input:

0

0
Output:

Example
Input
4
2 7 11 15
9
Output
0 1
