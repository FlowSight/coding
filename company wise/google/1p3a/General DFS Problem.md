Given an undirected graph, write a function to determine if there is a path from the starting node to the target node. The undirected graph is represented by node labels and a list of edges. Implement Depth-First Search (DFS) to solve this problem. Provide representative test cases.

Input Description:

Number of nodes n.
Number of edges m.
Next m lines, each containing two integers representing an edge between two nodes.
Starting node and target node.
Output Description:

Return True if there is a path from the starting node to the target node, otherwise return False.
Test Cases:

Input:
5 4
1 2
2 3
3 4
4 5
1 5
Output:
True

Input:
5 3
1 2
2 3
4 5
1 5
Output:
False
Constraints:

1 <= n, m <= 10^4
Node labels range from 1 to n.
Example
Input
5 4
1 2
2 3
3 4
4 5
1 5