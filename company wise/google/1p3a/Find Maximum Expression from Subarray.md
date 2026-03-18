Question
Given an integer array arr, find a contiguous subarray subarr such that the value x = min(subarr) + max(subarr) is maximized.

Input
An integer array arr with length in the range [1, 10^5] and element values within [-10^4, 10^4].
Output
Return the maximum possible value of x.
Example
Input: arr = [1, 3, 2, 5, 4]

Output: 10

Explanation: Select the subarray [5], where the minimum and maximum values are both 5, so x = 5 + 5 = 10.

Input: arr = [2, 1, 3]

Output: 4

Explanation: Select the subarray [2, 1] or [1, 3], both yield x = 3, whereas [2] or [3] themselves yield larger x.

Example
Input
[1, 3, 2, 5, 4]