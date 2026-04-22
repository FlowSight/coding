Write a program to output all possible paths starting from any given node in a directed graph.

Input:
Number of nodes n, numbered from 0 to n-1.
List of edges, each consisting of two nodes u and v, representing u -> v.
Starting node start.
Output:
A list of all possible paths starting from the given node, where each path is represented as a list of node numbers.
Example:
Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], start = 0

Output: [[0,1,3],[0,2,3]]

Constraints:
1 <= n <= 100
The graph is a directed acyclic graph.
1 <= |edges| <= n * (n - 1) / 2
The start node is guaranteed to exist in the graph.
Example
Input
4
[[0,1],[0,2],[1,3],[2,3]]
0