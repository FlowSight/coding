Given an undirected graph's edge list and some queries, for each query, count how many paths from the start node to the target node can form a palindrome. Each edge in the graph is marked with a character. Note that the path is considered a palindrome if the sequence of characters on the path forms a palindrome.

Input
An integer n, the number of nodes 2 <= n <= 500.
An integer m, the number of edges 1 <= m <= 1000.
A list of m tuples (from_i, to_i, char_i), representing an edge from from_i to to_i marked with char_i.
An integer q, the number of queries, 1 <= q <= 100.
A list of q tuples (start_i, end_i), representing queries from start point start_i to end point end_i.
Output
For each query, output how many paths can form a palindrome.
Example
Input:
n = 3, m = 3
edges = [(1, 2, 'a'), (2, 3, 'b'), (3, 1, 'a')]
queries = [(1, 3), (2, 1)]
Output:
[1, 1]
Note
The edges are bidirectional; paths can pass through the same node multiple times.
Example
Input
3 3
1 2 a
2 3 b
3 1 a
2
1 3
2 1