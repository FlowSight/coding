Problem
Given meeting intervals intervals, each as [start, end) (inclusive start, exclusive end), representing a meeting running from start to end.

Output the number of concurrent meetings over time:

Discretize the timeline into non-overlapping consecutive segments.
For each segment [segment_start, segment_end), output k, the number of meetings running throughout that segment.
I/O Contract (for an executable solution)
Read from stdin:

Line 1: integer n (# of meetings)
Next n lines: two integers start end
Output:

Multiple lines: segment_start segment_end k
Only output segments where k > 0.
Constraints
1 <= n <= 2e5
0 <= start < end <= 1e9
Example
Input:

3
0 30
5 10
15 20
Output:

0 5 1
5 10 2
10 15 1
15 20 2
20 30 1
Example
Input
3
0 30
5 10
15 20
Output
0 5 1
5 10 2
10 15 1
15 20 2
20 30 1