Problem
Given a binary tree, define your own Node class (with val, left, right) and implement an algorithm that computes the following in one run:

Sum of all node values in the tree, totalSum.
Maximum path sum maxPathSum: a path is any simple path between any two nodes in the tree following parent-child links (it may consist of a single node). The path sum is the sum of node values along the path.
Output one node-value sequence on a path achieving maxPathSum (from one endpoint to the other). If multiple maximum paths exist, output any.
Input
Line 1: integer n, number of nodes.
Next n lines: id val parentId describing node id with value val and its parent parentId (-1 means root).
Next n lines: id leftId rightId describing the left and right child ids of node id (-1 means null).
Output
Print three lines:

totalSum
maxPathSum
Space-separated integers: the node values along a maximum-sum path
Constraints
1 <= n <= 2 * 10^5
-1e9 <= val <= 1e9
The input forms a valid binary tree.
Target O(n) or O(n log n) time; avoid recursion stack overflow (use an explicit stack if needed).
Example
Input
1
0 5 -1
0 -1 -1
Output
5
5
5