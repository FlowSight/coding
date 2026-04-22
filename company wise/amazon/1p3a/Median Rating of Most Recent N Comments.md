Median Rating of Most Recent N Comments (Streaming)
You are implementing a comment system. Comments arrive as a stream; each comment has an integer rating.

Support two operations:

add x: append a new comment with rating x (can be negative or 0).
median: query the median rating among the most recent N comments (if fewer than N exist, use all of them).
Median definition:

If count is odd, return the middle value.
If count is even, return the average of the two middle values as a floating-point number (e.g., 2.5, 3.0).
Given window size N and a sequence of operations, output the result for each median query.

Input (stdin)
First line: integers N Q (window size, number of operations)
Next Q lines: either add x or median
Output (stdout)
For each median operation, print one line with the median.

Constraints
1 <= N <= 2e5
1 <= Q <= 2e5
-1e9 <= x <= 1e9
Must be efficient; do not sort the last N values on every query.
Sample Tests
See the Chinese section for 5 examples.

Example
Input
3 7
add 1
add 5
median
add 2
median
add 10
median
Output
3.0
2.0
2.0