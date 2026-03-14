There are n people labeled 0 to n-1. Initially, person 0 and firstPerson know a secret.

You are given a list meetings where meetings[i] = [xi, yi, ti] means xi and yi meet at time ti. Multiple meetings can happen at the same timestamp.

Rules:

If at the start of a meeting, at least one of the two attendees knows the secret, then after the meeting both know it.
Within the same timestamp t, the secret can propagate through multiple meetings (multi-hop) occurring at time t.
Return all people who know the secret after all meetings (any order).

Suggested Input Format
Line 1: n firstPerson m
Next m lines: xi yi ti
Suggested Output Format
One line: all people who know the secret (optionally sorted)
Constraints
2 <= n <= 1e5
1 <= m <= 2e5
0 <= xi, yi < n
1 <= ti <= 1e5
Sample Tests (5)
Input:

6 1 4
1 2 5
2 3 8
1 5 10
5 4 10
Output:

0 1 2 3 4 5
Input:

4 3 1
3 1 3
Output:

0 3 1
Input:

5 1 3
0 2 1
1 3 1
3 4 1
Output:

0 1 2 3 4
Input:

5 1 2
2 3 5
3 4 5
Output:

0 1
Input:

6 2 5
1 2 1
2 3 1
4 5 1
3 4 2
0 4 2
Output:

0 1 2 3 4
Example
Input
6 1 4
1 2 5
2 3 8
1 5 10
5 4 10
Output
0 1 2 3 4 5