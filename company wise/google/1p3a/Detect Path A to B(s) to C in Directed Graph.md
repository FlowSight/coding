Given a directed graph where each node's value is one of A, B, or C. Design an algorithm to determine whether there is a path A -> B -> C in the graph. The path can include one or more B nodes. Start a depth-first search from all A nodes. During the search, move only from A nodes to B nodes, and from B nodes to B nodes or C nodes. Return true if any B node has a neighbor C node.

Example
Input
graph = [Node('A'), Node('B'), Node('C')]