You are given a company reporting structure that forms a rooted tree with employees labeled 1..n, where 1 is the CEO (the root). You are given manager[] and reportee[] pairs (there are n-1 pairs), meaning reportee[i] directly reports to manager[i]. The pairs form a valid tree rooted at 1.

Compute the maximum reporting layer from the CEO to the farthest employee (i.e., the height of the rooted tree, measured as the number of nodes on the path).

Input:
Line 1: integer n
Next n-1 lines: two integers manager[i] reportee[i]
Output: one integer, the maximum reporting layer.
Constraints:

1 <= n <= 2*10^5
Example: Input:

5
1 2
1 3
3 4
4 5
Output:

4
Example
Input
1
Output
1