You are given the head of a linked list. Each node has:

val: an integer
next: pointer to the next node (or null)
random: pointer to any node in the list or null
extra: pointer to any node in the list or null (an additional arbitrary pointer besides random)
Return a deep copy of the list.

A deep copy means:

All nodes in the new list are newly created
The next/random/extra relationships are preserved in the copied list
No pointer in the copied list points to any original node
Constraints
Number of nodes n: 0 <= n <= 1e5
random and extra can be null or point to any node in the list
Target time complexity: O(n)
Example scenarios (conceptual)
Empty list
Single node with random/extra pointing to itself
Multiple nodes with cross references
All random/extra are null
Large list for performance validation
Example
Input
(conceptual) head = null
Output
null