Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the input intervals.

Input
intervals: An array of intervals, intervals[i] = [start_i, end_i], where 0 <= len(intervals) <= 10^4.
start_i and end_i are integers, 0 <= start_i <= end_i <= 10^4.
Output
Return an array of non-overlapping intervals sorted by the start time.
Example
Input
[[1,3],[2,6],[8,10],[15,18]]