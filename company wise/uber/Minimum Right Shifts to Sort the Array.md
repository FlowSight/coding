You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.

A right shift is defined as shifting the element at index i to index (i + 1 % n), for all indices.

Function Description

Complete the function minimumRightShiftsToSortArray in the editor.

minimumRightShiftsToSortArray has the following parameter:

int[] nums: a 0-indexed array containing distinct positive integers
Returns

int: the minimum number of right shifts required to sort nums, or -1 if it is not possible

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
nums contains distinct integers.
Example
Input
nums = [3,4,5,1,2]
Output
2