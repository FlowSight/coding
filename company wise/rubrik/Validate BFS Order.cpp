You are given two arrays vec1 and vec2 of the same length m. For each index i, there is an undirected edge between vec1[i] and vec2[i].

You are also given a rule: within the same vector, earlier elements have higher hierarchy (closer to the root), and later elements have lower hierarchy. Under this constraint, the edges form a tree with n nodes (node labels are integers).

You are given q queries. Each query is a sequence order of length n, representing the dequeue order of a BFS traversal starting from the root (FIFO queue).

For each query, determine whether order can be a valid BFS dequeue order of this tree (nodes in the same level may appear in any order, but the sequence must respect BFS layering and queue behavior).

I/O
Input provides vec1, vec2, and q query sequences.
Output true/false for each query.
Constraints (to be filled)
n: number of nodes
m: number of edges (typically m = n-1)
q: number of queries
Example
vec1 = [1,1,4], vec2 = [3,2,3] forms the tree:

1
| \
3  2
|
4
order = [1,2,3,4] is a valid BFS order.