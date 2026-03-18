
Given two time-sorted lists, SoT and queries, for each query, find the smallest element in SoT that is greater than or equal to query and return its value. If no such element exists, return -1.

You need to implement an efficient algorithm for this task. You may use binary search to achieve this.

Test cases:

SoT: [1, 2, 5, 7, 8], queries: [0, 3, 6, 10] Output: [1, 5, 7, -1]

SoT: [4, 10, 15], queries: [4, 5, 14] Output: [4, 10, 15]

SoT: [1, 2], queries: [0, 1, 2, 3] Output: [1, 1, 2, -1]

SoT: [], queries: [0, 1] Output: [-1, -1]

SoT: [3, 5, 7], queries: [4, 5, 6] Output: [5, 5, 7]

Example
Input
[1, 2, 5, 7, 8]
[0, 3, 6, 10]