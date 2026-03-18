Given a binary tree and two nodes p and q in the tree, find their lowest common ancestor. The lowest common ancestor is defined as the deepest node that has both p and q as descendants. Note: A node can be a descendant of itself.

Binary tree node is defined as follows:

class TreeNode:
    def __init__(self, value=0, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
Input:

The root of a binary tree root.
Two nodes p and q in the tree.
Output:

The lowest common ancestor node of p and q.
Constraints:

The number of nodes in the tree is no more than 10^4.
All node values are unique.
Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: Node 3 is the lowest common ancestor of nodes 5 and 1.
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: Node 5 is the lowest common ancestor of nodes 5 and 4.
Example
Input
root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1