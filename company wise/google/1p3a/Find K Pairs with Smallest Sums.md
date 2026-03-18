Given two arrays arr1 and arr2 and an integer k, find the indices pairs (i, j) such that arr1[i] + arr2[j] have the smallest sums up to the k-th smallest sum.

Example
Input: arr1 = [1,7,11], arr2 = [2,4,6], k = 3

Output: [[0,0],[0,1],[0,2]]

Explanation: The smallest sums are 1+2=3, 1+4=5, 1+6=7. Indices pairs are (0,0), (0,1), (0,2).

Requirements
Use a min-heap. Each time, extract the smallest (i, j) from the heap, and add (i, j+1) if valid. Repeat this process k times.

Constraints
The lengths of both arrays do not exceed 1000.
The number range is [-10^9, 10^9].
Example
Input
[[1,7,11], [2,4,6], 3]