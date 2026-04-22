You are given an integer array a of length n.

Repeat the following operation until no elements remain:

Pick the currently existing element with the minimum value a[i] (if multiple minima exist, you may pick any).
Add it to the answer: ans += a[i].
Delete this element and its adjacent elements: if i-1 still exists, delete a[i-1]; if i+1 still exists, delete a[i+1].
Return the final ans.

Input

Line 1: integer n
Line 2: n integers a[i]
Output

One integer ans
Constraints (assumed)

1 <= n <= 2e5
-1e9 <= a[i] <= 1e9
Example Input:

5
3 1 2 4 5
Output:

6
(Example illustrates the rule; the exact tie-break among equal minima is not important.)

Example
Input
1
10
Output
10