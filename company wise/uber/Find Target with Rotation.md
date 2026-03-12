Given an array and a target value, find how many times the elements in the array can be rotated to obtain the target value. The rotation operation involves moving the first digit of the array elements to the last. Write a function to solve this problem. The function signature is def find_rotated_target(arr: List[int], target: int) -> int. You can assume all elements are positive integers.

Input:

A list of integers arr
An integer target
Output:

The number of times the rotated array can obtain the target value
Example:

find_rotated_target([1, 2, 3, 4, 5], 12345)  # Returns 0
find_rotated_target([5, 3, 2, 1, 4], 45123)  # Returns 1
Constraints:

The maximum length of arr is 10000
Each rotation moves the first element of the array to the end
Example
Input
[1, 2, 3, 4, 5]
12345