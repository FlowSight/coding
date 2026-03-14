Given a tree with N nodes, numbered from 0 to N-1, and N-1 undirected edges. The task is to calculate the sum of distances from each node to all other nodes.

Input
An integer N representing the number of nodes, guaranteed 1 <= N <= 3*10^4.
An array of edges with length N-1, where edges[i] = [ai, bi] indicates an undirected edge between nodes ai and bi.
Output
An array of N integers answer, where answer[i] is the sum of distances from the ith node to all other nodes.
Example
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation:
For node 0, the distances are |0-1| + |0-2| + |0-3| + |0-4| + |0-5| = 8,
For node 1, the distances are |1-0| + |1-2| + |1-3| + |1-4| + |1-5| = 2 + 4 + 4 + 4 = 12, and so on.
Example
Input
6
[[0,1],[0,2],[2,3],[2,4],[2,5]]
Output
[8,12,6,10,10,10]