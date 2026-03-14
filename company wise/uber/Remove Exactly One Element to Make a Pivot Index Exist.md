Problem: Remove Exactly One Element to Make a Pivot Index Exist
Given an integer array nums (values may repeat and may be negative), you must remove exactly one element (remove one index). After removal, the array length decreases by 1 and the remaining elements keep their relative order.

An index p in an array arr is a pivot index if and only if:

sum(arr[0..p-1]) == sum(arr[p+1..end])
(i.e., the sum of elements strictly to the left of p equals the sum of elements strictly to the right of p; arr[p] is excluded from both sides.)

Return True if there exists a way to remove exactly one element such that the resulting array has at least one pivot index; otherwise return False.

Input format (suggested)
First line: integer n
Second line: n integers for nums
Output
Print True or False
Constraints
2 <= n <= 2*10^5
-10^9 <= nums[i] <= 10^9
Example
Input
5
1 7 3 6 5
Output
True