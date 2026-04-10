You are given an integer array experiences where experiences[i] is the duration (in hours) of the i-th experience. You have layover hours to spend and want to book experiences to exactly fill the layover time.

Rules:

You may book any number of experiences.
Each experience duration can be booked repeatedly (unlimited usage).
Decide whether there exists a selection whose total duration is exactly layover.
Output true if possible, otherwise false.

Input (stdin)

Line 1: two integers n and layover.
Line 2: n integers for experiences.
Output (stdout)

One line: true or false.
Constraints

1 <= n <= 200
1 <= experiences[i] <= 1e4
0 <= layover <= 1e4
Example:

Input: 2 10 and 2 3
Output: true (e.g., 2+2+3+3=10)


experience layover 那题, 有 list of experiences [2.0, 3.6] 代表experience需要的时间， 要book experience to fill layover hours 要求exactly fill，可以重复book

经典dp 完全背包 国人大哥非常nice


-------------

