Problem
Given the root root of a binary tree, compute the average value of the nodes on each level using level-order traversal (BFS), and output the averages from top to bottom.

If a level has k nodes, its average is the sum of values on that level divided by k.
Each level’s average should be printed as a floating-point number.
Input (stdin)
The binary tree is provided in level-order array form, where null indicates a missing child.

Line 1: a space-separated sequence representing the tree (e.g., 3 9 20 null null 15 7).
Output (stdout)
Print the per-level averages in one line, space-separated, from the root level to the deepest level.

Constraints
Number of nodes n: 0 <= n <= 1e5
Node values: -1e9 <= val <= 1e9
Target complexity: O(n) time.
Examples
Example 1 Input:

3 9 20 null null 15 7
Output:

3 14.5 11
Example 2 Input:

1
Output:

1
Example
Input
3 9 20 null null 15 7
Output
3 14.5 11