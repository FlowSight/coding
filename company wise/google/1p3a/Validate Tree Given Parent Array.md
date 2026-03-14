Problem: Validate a Tree Given a Parent Array
You are given an array parent of length n, where parent[i] is the parent index of node i.

If parent[i] = -1, node i is a root.
Node indices are 0..n-1.
Determine whether these parent-child relations form a valid rooted tree. Output true/false.

A valid rooted tree must satisfy:

There is exactly one root (exactly one -1).
Every non-root node has exactly one parent, and each parent index must be within [0, n-1].
The structure contains no cycles.
The root can reach all nodes (i.e., the structure is connected).
Input
Line 1: integer n
Line 2: n integers representing parent
Output
Print true or false
Constraints
1 <= n <= 2 * 10^5
parent[i] ∈ [-1, 0..n-1] (invalid values may appear; treat them as false)
Examples
Example 1:

5
-1 0 0 1 1
Output:

true
Example 2 (multiple roots):

3
-1 -1 0
Output:

false
Example 3 (cycle):

3
-1 2 1
Output:

false
Example
Input
5
-1 0 0 1 1
Output
true