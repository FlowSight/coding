Given an undirected (bidirectional) graph, each edge (u, v) has a value w representing a transformation from u to v. Because the graph is bidirectional, a reverse transformation exists as well.

Answer multiple queries: for each pair (s, t), return the composed result along some path from s to t. If s and t are disconnected, return -1.

Implement:

Input: n, m, then m lines u v w, then q, then q queries s t.
Output: one result per query.
Constraints:

1 <= n,m,q <= 2e5
Nodes labeled 0..n-1
w positive (integer or float; clarify in interview)
Aim for near O((n+m+q) α(n)) (weighted DSU) or O((n+m) log n + q log n).
You must clarify in the interview:

The composition operator (multiply vs add)
How to derive the reverse relation (reciprocal vs negation)
Floating-point tolerance requirements.