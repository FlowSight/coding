You are given a tree T with N nodes and the tree rooted at node 1. Every node has a character C[i] assigned to it. You are given Q queries of the following format:

Query: u

You must find whether string S that is generated for node u is palindromic or not. String S for a node u is generated as follows:

S = Empty

makeString(u)

{

For all v = Child of u

makeString(v)

S += C[u];

}

Child of v should be traversed in order of increasing Node number

Input format

The first line contains an integer N.
Next N — 1 lines contain two space-separated integers u and v denoting an edge between node u and node v.
The next line contains N space-separated characters denoting C[i] for all i from 1 to N.
The next line contains an integer Q.
Next Q lines contain an integer u denoting the node for the query.
Output format

Print Q lines and in each line, print 1 if S is palindromic. Otherwise, print 0.

Note: Use fast I/O

Constraints: 1 ≤ N, Q ≤ 200000
|C[i]| contains lowercase Latin Letters.

Example
Input
n = 5
edges = [[1, 2], [1, 3], [2, 4], [2, 5]]
c = ['a', 'b', 'a', 'b', 'c']
queries = [1, 2]
Output
[0, 1]