Problem: Minimum Jumps in a Circular Array (Exact Left/Right Jumps)
You are given a circular array arr of length n (indices 0..n-1). When you are at position i, you must jump exactly arr[i] steps, and you may choose either direction:

Jump right to: (i + arr[i]) mod n
Jump left to: (i - arr[i]) mod n
Given start index from and target index to, compute the minimum number of jumps needed to reach to from from.

If it is impossible to reach, return -1.
Input
Line 1: integer n
Line 2: n integers representing arr
Line 3: two integers from and to
Output
One integer: the minimum number of jumps (or -1 if unreachable)
Constraints (suggested)
1 <= n <= 2 * 10^5
0 <= arr[i] <= 10^9
0 <= from, to < n
Example
n = 5
arr = [2, 1, 2, 2, 1]
from = 0, to = 3
From index 0 you can jump to 2 or 3 (left jump is -2 mod 5 = 3), so the answer is 1.

Example
Input
5
2 1 2 2 1
0 3
Output
1