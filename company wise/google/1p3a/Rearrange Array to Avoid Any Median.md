Given an array of natural numbers with length n, rearrange the array such that the median of any pair (a[i], a[j]) is not between those two numbers. Return True if such a rearrangement is possible, False otherwise. The median value between any two numbers is defined as their average 2.0.

Example:

Input: [1, 2, 3] Output: False Explanation: Any rearrangement results in a pair where the median falls between them.

Input: [1, 2, 4] Output: True Explanation: Possible rearrangement is [2, 4, 1].

Constraints:

The length of the array n can be up to 1000.
The array elements range from 1 to 10^6.
Example
Input
[1, 2, 3]