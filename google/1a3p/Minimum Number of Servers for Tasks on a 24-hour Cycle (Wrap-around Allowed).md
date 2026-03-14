Problem: Minimum Number of Servers (24-hour cycle, wrap-around allowed)
You are given a set of tasks running on servers. Each task is represented by a pair (start, duration):

start: the start time in minutes within a day, 0..1439.
duration: the running time in minutes (positive), which may exceed 1440, so a task may extend into the next day(s).
Once started, a task runs continuously until it finishes.
A server can run at most one task at any time.
Time is displayed on a 24-hour cycle (mod 1440), but the actual occupation happens on a continuous timeline.
Return the minimum number of servers required to run all tasks.

Input format (suggested)
First line: integer n, number of tasks
Next n lines: two integers start duration
Output format
One integer: the minimum number of servers
Constraints
1 <= n <= 2*10^5
0 <= start < 1440
1 <= duration <= 10^9
Example
Tasks:

(23*60, 60) runs 23:00–24:00
(0, 30) runs 00:00–00:30
(23*60, 30) runs 23:00–23:30
Output: 2

Example
Input
3
1380 60
0 30
1380 30
Output
2