Given an array of meeting time intervals, find the minimum number of meeting rooms required. Each meeting is represented by a start and end time, such as (start, end). How can plans be optimized for meetings scheduled far in the future?

Input
A list of n integer pairs where each pair represents the start and end times of a meeting.
Output
The minimum number of meeting rooms required.
Example
Input: [(0, 30), (5, 10), (15, 20)] Output: 2

Input: [(7, 10), (2, 4)] Output: 1

Constraints
1 <= n <= 10^4
Optimize future meetings using binary search.
Example
Input
[(0,30),(5,10),(15,20)]