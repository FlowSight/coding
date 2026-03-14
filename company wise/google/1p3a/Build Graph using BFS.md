Perform a breadth-first search on a graph to find a specific node.

Write a function to perform this, using an adjacency list representation.
Given the starting node and the target node, return the shortest path between them.
Devise a method to optimize the graph construction to avoid naive graph building.
Example:

Input:
Graph: {1: [2, 3], 2: [4], 3: [4], 4: []}
Start node: 1
Target node: 4

Output: [1, 2, 4]
Assume: No negative weights in edges, no cycles.

Example
Input
{1: [2, 3], 2: [4], 3: [4], 4: []}
1
4
Output
[1, 2, 4]