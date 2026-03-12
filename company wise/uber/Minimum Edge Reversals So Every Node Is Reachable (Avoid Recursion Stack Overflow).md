You are given a tree with n nodes labeled 0..n-1, but each undirected edge is assigned a direction, producing n-1 directed edges. edges[i] = [u, v] denotes a directed edge u -> v.

For every node r as a starting node, compute the minimum number of edges that must be reversed (turn x -> y into y -> x) so that all nodes become reachable from r by following directed edges.

Return an array ans of length n where ans[r] is that minimum for root r.

Requirements:

Target O(n) or O(n log n) time.
Recursive DFS may stack overflow; use iterative DFS/BFS or an explicit stack.
Input (stdin):

Line 1: integer n
Next n-1 lines: two integers u v meaning a directed edge u -> v
Output (stdout):

One line with n integers ans[0..n-1]
Constraints:

2 <= n <= 200000
0 <= u, v < n
The underlying undirected graph is a tree
Example: Input:

4
0 1
2 0
3 2
Output:

1 2 1 0
Example
Input
4
0 1
2 0
3 2
Output
1 2 1 0