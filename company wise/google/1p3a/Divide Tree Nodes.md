You are given an undirected tree with N nodes. Each node of the tree is assigned to a value. You are required to divide the nodes into as little groups as possible, such that no two nodes in the group are adjacent to each other. Consider a group G. Let us consider a pair (u,v) from the group. The value of pair (u,v) is given as |A[u] - A[v]| where A[x] is the value assigned to node x (1<=x<=n). The cost of group G is defined as the maximum sum you can get by pairing up the nodes at G. Each node can be used only once to make a pair. It is possible for some nodes in G to be unpaired. Find the sum of costs of all possible that can be made for the given tree.

Input Description

First line containing T - number of test cases. First line of each test case containing N - number of nodes. Second line of each test case containing N space separated integers denoting array A[]. Next N-1 lines contain U and V denoting an edge between the nodes U and V.

Constraints:

1 ≤ T ≤ 10
1 ≤ N ≤ 105
1 ≤ A[i] ≤ 109
1 ≤ U, V ≤ N
Example
Input
n = 5
A = [12, 17, 14, 13, 16]
edges = [[1, 2], [1, 3], [1, 5], [2, 4]]
Output
4