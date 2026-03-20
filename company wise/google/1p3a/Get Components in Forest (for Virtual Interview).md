Given a binary tree with n nodes and an array edges where each element is of the form [from, to], representing an edge from from to to.

Remove all the edges in the edges array from the tree and return an array with the total node count in each connected component formed after removing all the edges from the tree.

Note: All the node values in the Binary Tree are unique.

Constraints: ``

Example
Input
Nodes = ["1", "2", "3", "4", "5", "null", "null"]
Edges = [[1, 2], [2, 4]]
Output
[2,2,1]