Given an integer array nums and an integer k, return the number of good subarrays of nums.

A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].

A subarray is a contiguous non-empty sequence of elements within an array.

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i], k <= 10^9
Example
Input
nums = [1,1,1,1,1]
k = 10
Output
1