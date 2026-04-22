You are given two arrays of equal length requiredTime and spentTime:

requiredTime[i] is the total time needed to finish task i.
spentTime[i] is the time already spent on task i.
You also have an additional x units of time that can be allocated to any tasks.

Define the remaining time of task i as:

remain[i] = requiredTime[i] - spentTime[i]
A task is considered completed once its total invested time reaches requiredTime[i].

Return the maximum number of tasks that can be completed by allocating the extra time x optimally.

Input format

Line 1: integer n
Line 2: n integers for requiredTime
Line 3: n integers for spentTime
Line 4: integer x
Output format

One integer: the maximum number of tasks that can be completed.
Example

Input:

5
4 3 7 2 5
1 3 4 0 3
6
Output:

3
Explanation: remaining times are [3,0,3,2,2]. With x=6, you can complete at most 3 tasks (e.g., those with remaining time 0,2,2).

Example
Input
5
4 3 7 2 5
1 3 4 0 3
6
Output
3