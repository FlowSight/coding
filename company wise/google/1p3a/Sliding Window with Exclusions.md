Given an integer array nums, an integer windowSize, and an integer k, implement a sliding window on the array such that for each sliding window, you remove the largest k elements from the current window and return the average of the remaining elements. Return a new array where each element is the average derived from each sliding window's operation over the array. The window slides one position at a time until the end of the array.

Input Description:

nums: An integer array.
windowSize: Size of the sliding window.
k: Number of largest numbers to remove.
Output Description:

Return a list containing the average computed after sliding the window.
Example 1:

Input: nums = [1, 3, 7, 8, 5, 6, 4], windowSize = 3, k = 1

Output: [5.0, 5.5, 5.0, 5.0, 5.0]

Explanation:

For the first window, [1, 3, 7], remove the largest 1 number, remaining [1, 3], average is 2.0
For the second window, [3, 7, 8], remove the largest 1 number, remaining [3, 7], average is 5.0
Example
Input
7
1 3 7 8 5 6 4
3
1