Problem: Binary Tree 3-Step Computation (Total Sum / Max Path Sum / Output Path Nodes)
Given a binary tree where each node stores an integer val and has left and right pointers. You must implement the Node class/struct yourself.

Complete the following tasks:

Compute the sum of all node values in the tree.
Compute the maximum path sum in the binary tree:
A path can start and end at any nodes.
The path must follow parent-child pointers continuously.
The path contains at least one node.
The path sum is the sum of node values along the path.
Output one path (node values) that achieves the maximum path sum:
Output the node values from the start to the end of the path.
If multiple maximum paths exist, returning any one is acceptable.
Input Format (implementation convention for this problem)
Line 1: integer n, number of nodes.
Line 2: n integers vals[0..n-1].
Next n lines: two integers l r for node i's left/right child indices:
l is the left child index, r is the right child index.
Use -1 if the child does not exist.
Node 0 is the root.
Output Format
Print 3 lines:

total sum of all nodes
maximum path sum
one maximum path as space-separated node values
Constraints
1 <= n <= 2 * 10^5
-10^9 <= vals[i] <= 10^9
The input is a valid tree reachable from the root
Example
Input:

3
1 2 3
1 2
-1 -1
-1 -1
One valid output:

6
6
2 1 3
Example
Input
3
1 2 3
1 2
-1 -1
-1 -1
Output
6
6
2 1 3