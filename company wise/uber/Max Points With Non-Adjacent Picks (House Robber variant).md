Given an array nums of length n (nums[i] is the score/benefit you gain by choosing index i), select a set of indices such that:

You cannot select two adjacent indices (i.e., if you pick i, you cannot pick i-1 or i+1).
Return the maximum total score you can obtain.

Follow-ups:

Analyze the time and space complexity of your algorithm.
Optimize the space usage if possible without changing time complexity.
Add a feature: return not only the maximum score but also one optimal strategy (the list of chosen indices). If multiple optimal solutions exist, return any.
Suggested Input Format
Line 1: integer n
Line 2: n integers nums[i]
Suggested Output Format
Line 1: maxScore
(Advanced) Line 2: indices of one optimal strategy (space-separated)
Constraints
1 <= n <= 2 * 10^5
0 <= nums[i] <= 10^9
Sample Tests (5)
Input:

4
1 2 3 1
Output:

4
Input:

5
2 7 9 3 1
Output:

12
Input:

1
5
Output:

5
Input:

3
0 0 0
Output:

0
Input:

6
10 1 1 10 1 10
Output:

30
Example
Input
4
1 2 3 1
Output
4