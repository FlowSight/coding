Given a set of non-overlapping intervals, insert a new interval into these intervals (first problem), then merge on the set of intervals after insertion (second problem). The interval endpoints are sorted, but there might exist overlapping intervals.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5] Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8] Output: [[1,2],[3,10],[12,16]]

Constraints
intervals[i][0] <= intervals[i][1]
newInterval is a valid interval and is already sorted.
Write a function to complete the above functionality, accurately inserting and merging intervals.

Example
Input
[[[1,3],[6,9]], [2,5]]