Problem: Minimum Edge Reversals (Re-rooting DP)
You are given a tree with n nodes labeled 1 to n. The input provides n-1 directed edges edges, each given as [u, v] meaning there is a directed edge u -> v.

You may reverse any edge (change u -> v to v -> u) with cost 1 per reversal.

For every node r (1 <= r <= n), compute the minimum number of reversals needed so that starting from r, you can reach all other nodes by following directed edges.

Return an array ans of length n, where ans[r] is the answer when the root is r (output in node order 1..n).

Input (stdin)
Line 1: integer n
Next n-1 lines: two integers u v representing a directed edge u -> v
Output (stdout)
One line: n integers: ans[1] ans[2] ... ans[n]
Constraints
2 <= n <= 2 * 10^5
The underlying undirected graph is a tree
Nodes are 1-indexed
Examples
Input:

4
1 2
2 3
4 2
Output:

2 1 2 2
Input:

3
1 2
2 3
Output:

0 1 2
Input:

3
2 1
2 3
Output:

1 0 1
Input:

5
1 2
1 3
4 3
5 4
Output:

0 1 1 2 3
Input:

2
2 1
Output:

1 0
Example
Input
4
1 2
2 3
4 2
Output
2 1 2 2