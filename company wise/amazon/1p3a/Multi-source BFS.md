Given a graph with multiple source nodes, use multi-source breadth-first search (BFS) to find the shortest path from these source nodes to all other nodes. Implement this algorithm and describe its process.

Requirements:

Input is a graph represented by a list of nodes and edges (edges are represented by pairs of nodes), and a list of source nodes.
Output is a dictionary with nodes as keys and shortest path distances as values.
Input Constraints:

Maximum number of nodes is 10^4.
Maximum number of edges is 2 * 10^4.
Example:

Input: Nodes list: ['A', 'B', 'C', 'D'] Edges list: [['A', 'B'], ['B', 'C'], ['A', 'C'], ['C', 'D']] Source nodes: ['A', 'D']

Output: {'A': 0, 'B': 1, 'C': 1, 'D': 0}

Example
Input
['A', 'B', 'C', 'D']
[['A', 'B'], ['B', 'C'], ['A', 'C'], ['C', 'D']]
['A', 'D']