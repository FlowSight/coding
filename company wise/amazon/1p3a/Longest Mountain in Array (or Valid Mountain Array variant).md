Problem: Longest Mountain in an Array
Given an integer array arr, return the length of the longest mountain subarray.

A mountain is a contiguous subarray arr[l..r] such that:

r - l + 1 >= 3
There exists a peak index p (l < p < r) where:
arr[l] < arr[l+1] < ... < arr[p]
arr[p] > arr[p+1] > ... > arr[r]
Return 0 if no mountain exists.

Input/Output
Input:
Line 1: integer n
Line 2: n integers for array arr
Output:
One integer: the longest mountain length
Constraints
1 <= n <= 2 * 10^5
-10^9 <= arr[i] <= 10^9
Examples
input:
7
2 1 4 7 3 2 5
output:
5
input:
3
2 2 2
output:
0
input:
5
0 1 2 3 4
output:
0
input:
5
4 3 2 1 0
output:
0
input:
10
1 2 3 2 1 2 3 4 3 2
output:
5
Example
Input
7
2 1 4 7 3 2 5
Output
5