Problem: Binary Search on Answer — Minimum Workers to Meet a Target Time
You are given n tasks, where task i has workload tasks[i] (positive integers). You can hire some workers to process tasks in parallel. Each worker must take a contiguous block of tasks (i.e., partition the array into contiguous segments), and each task is assigned to exactly one worker.

For a given number of workers k, the completion time is defined as the maximum segment sum among the k assigned segments (the busiest worker’s total workload).

Given a target time/efficiency threshold T, compute the minimum number of workers required so that, under an optimal assignment, the completion time is <= T.

Input (stdin)
Line 1: two integers n and T
Line 2: n integers tasks[i]
Output (stdout)
One integer: the minimum number of workers needed
Constraints
1 <= n <= 2*10^5
1 <= tasks[i] <= 10^9
1 <= T <= 10^18
Example
Input:
n=5, T=6
tasks=[1,2,3,4,5]
Output:
3
Example
Input
5 6
1 2 3 4 5
Output
3
