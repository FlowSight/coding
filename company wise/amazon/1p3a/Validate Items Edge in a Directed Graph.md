Given a directed graph composed of items, determine if there is an infinite loop in these dependencies.

Input
An integer n representing the number of nodes in the graph.
A list edges, where each element is a tuple (u, v), indicating a directed edge from item u to item v.
Output
Return true if there are no cycles among the items. Otherwise, return false.
Example
Input:

4
[(0, 1), (1, 2), (2, 3), (3, 1)]
Output:

false
Constraints
The number of nodes n is a non-negative integer.
Each node is numbered from 0 to n-1.
Example
Input
4
[(0, 1), (1, 2), (2, 3), (3, 1)]