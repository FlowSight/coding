Given a full range [start, end] of all integers and an unsorted list of integers numbers, find the missing integers within the range. Replace all sequences of three or more consecutive missing numbers with a "-".

Example:

Input: start = 1, end = 10, numbers = [1, 2, 4, 7, 8, 10] Output: [3, '5-6', 9]

Constraints:

Both start and end are integers, and end >= start
numbers is a subset of the range [start, end]
Numbers in numbers are unique and sorted in ascending order
Example
Input
1
10
6
1
2
4
7
8
10