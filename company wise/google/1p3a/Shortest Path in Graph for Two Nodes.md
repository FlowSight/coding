Given an undirected graph and two nodes A and B, both aiming to reach node D, they can arrive at D separately or meet at some node and proceed to D together. Find the shortest total path length for both to reach node D.

Input:
An adjacency list representing the undirected graph
Two nodes A and B
Output:
The shortest total path length for both to reach node D.
Example:
Input: graph = {1: [2, 3], 2: [4], 3: [4], 4: []}, A = 1, B = 2, D = 4 Output: 3

Explanation:
Node A shortest path from 1 to 4 is 1 -> 2 -> 4
Node B shortest path from 1 to 4 is 1 -> 2 -> 4
Total shortest path length is (1 -> 2 -> 4) + (2 -> 4) = 3
Example
Input
graph = {1: [2, 3], 2: [4], 3: [4], 4: []}, A = 1, B = 2, D = 4