Given a linked list, extract all nodes that satisfy a specific condition. Implement a function extract_nodes(linked_list, condition) where linked_list is the head node of the list and condition is a function that determines whether a node satisfies the condition. The function should return a new linked list containing all nodes that meet the condition, preserving the original order.

Input:
A linked list linked_list with integer node values.
A predicate function condition, with inputs as list nodes, returning True if the node meets the condition.
Output:
A head node of a new linked list containing only the nodes that meet the condition.
Example:
Input: linked_list = 1 -> 2 -> 3, condition = lambda x: x % 2 == 0
Output: 2
Constraints:
The linked list can contain up to 1,000 nodes.
Node values range from -10,000 to 10,000.
Example
Input
1, 2, 3; lambda x: x % 2 == 0