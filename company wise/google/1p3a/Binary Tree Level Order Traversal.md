Given a binary tree, consider implementing a function to traverse the tree level by level from left to right and return the values of nodes for each level.

Input:
A binary tree represented as a TreeNode class, where TreeNode includes properties val, left, and right.
Output:
A list of lists where each sublist represents the values of nodes at that level of the tree.
Example:
Input: [3,9,20,null,null,15,7]
Output: [
  [3],
  [9,20],
  [15,7]
]
Note:
The height of the tree does not exceed 1000.
The number of nodes does not exceed 5000.
Example
Input
3 9 20 null null 15 7