Given an integer array points and an integer target, calculate the number of ways you can sum the elements of the array to reach the target value. You can assume all numbers are positive integers, and elements in the array can be used indefinitely.

Input

An integer array points consisting of positive integers.
A positive integer target.
Output

An integer representing the total number of ways the target sum can be achieved.
Example

Input: points = [1, 2, 3], target = 4
Output: 7
Explanation: Possible combinations are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Constraints

The length of points is [1, 50].
All elements of points are positive integers and do not exceed 1000.
target value does not exceed 1000.
Example
Input
points = [1, 2, 3]
target = 4