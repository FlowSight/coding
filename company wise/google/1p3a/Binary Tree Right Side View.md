Given a binary tree, return the values of the nodes you can see when looking from the right side.

Example
Input: Binary tree [1, 2, 3, null, 5, null, 4]

    1
   / \
  2   3
   \   \
    5   4
Output: [1, 3, 4]

Requirements
Use breadth-first search (BFS) algorithm. For each level, output the last node in that level.

Constraints
The number of nodes in the tree is in the range [0, 100].
-100 <= Node value <= 100
Example
Input
[1, 2, 3, null, 5, null, 4]