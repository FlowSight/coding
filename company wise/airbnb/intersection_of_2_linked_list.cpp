Given two (singly) linked lists, return the node at which the two lists intersect. If the two linked lists have no intersection at all, return null. Note that the linked lists might contain cycles.

Example 1:

Input: listA = [4,1,8,4,5], listB = [5,6,1,8,4,5]
Output: ListNode(8)
Explanation: The two linked lists intersect at node with value 8.
Example 2:

Input: listA = [1,9,1,2,4], listB = [3,2,4]
Output: ListNode(2)
Explanation: The two linked lists intersect at node with value 2.
Example 3:

Input: listA = [2,6,4], listB = [1,5]
Output: null
Explanation: The two linked lists do not intersect, therefore return null.
Note:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
Example
Input
listA = [4,1,8,4,5], listB = [5,6,1,8,4,5]
Output
ListNode(8)