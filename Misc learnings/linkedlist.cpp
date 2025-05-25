//reversing list the assigning has to be like ... rhs == next lines lhs
// prev = cur;
// cur = prev;
// way slow...has to be within 15 mins with dry run..

// halving...or finding kth index from end...has some patterns
// either do index wise
// like ...mid element means n/2 (0 based index)
// 3 sized list ...ans is index 1
// 4 sized list ...ans is index 1
// 5 sized list ...ans is index 2
// so slow->next and fast->next->next

ListNode* half(ListNode* head){
    ListNode* slow = head;
    ListNode* fast = head;
    while(slow && slow->next && fast && fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//https://leetcode.com/problems/intersection-of-two-linked-lists/solutions/49785/java-solution-without-knowing-the-difference-in-len/
//same pattern applies for lca with parent
public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
    //boundary check
    if(headA == null || headB == null) return null;
    
    ListNode a = headA;
    ListNode b = headB;
    while( a != b){
    	//for the end of first iteration, we just reset the pointer to the head of another linkedlist
        a = a == null? headB : a.next;
        b = b == null? headA : b.next;    
    }
    
    return a;
}
