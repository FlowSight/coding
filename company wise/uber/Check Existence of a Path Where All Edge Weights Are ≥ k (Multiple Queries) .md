You are given an undirected weighted graph with n nodes labeled 0 to n-1, and an edge list edges where each edge is (u, v, w) representing an undirected edge between u and v with weight w.

You will receive multiple queries queries, where each query is (a, b, k).

For each query, determine whether there exists a path from node a to node b such that every edge on the path has weight >= k.

Return a boolean array ans of the same length as queries, where ans[i] corresponds to the i-th query, in the original order.

Input (conceptual)
n: number of nodes
edges: list of edges (u, v, w)
queries: list of queries (a, b, k)
Output
A boolean array of length len(queries).
Constraints (typical for LeetCode 1697)
1 <= n <= 1e5
0 <= u, v < n
1 <= w <= 1e9
1 <= len(edges), len(queries) <= 1e5
Example
Example 1

n = 3
edges = [(0,1,2),(1,2,4),(0,2,8)]
queries = [(0,2,5),(0,2,9),(0,1,2)]
Output:

[True, False, True]
Example
Input
3
3
0 1 2
1 2 4
0 2 8
3
0 2 5
0 2 9
0 1 2
Output
true
false
true