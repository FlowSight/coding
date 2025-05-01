// 28 apr 2025
// clean  10 mins

// 12 feb 2025..
// 8 mins..
// one logical error
// 1 compiler error..
// verdict : FAIL
// sev2

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int cur = 0, carry = 0;
        ListNode* dummyNode = new ListNode();
        ListNode* prevNode = dummyNode;
        while(l1 || l2 || carry) {
            cur = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            carry = cur/10;
            cur = cur%10;
            prevNode->next = new ListNode(cur);

            prevNode = prevNode->next;
            if(l1)l1 = l1->next;
            if(l2)l2 = l2->next;
        }
        return dummyNode->next;
    }
};



// 13 jan 2025..
// 11 mins
// verdict : pass

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int cur = 0, carry = 0;
        ListNode* curnode = new ListNode();
        ListNode* dummyHead = curnode;
        while(l1 || l2){
            cur = carry+ (l1?l1->val:0) + (l2?l2->val:0);
            curnode->next = new ListNode(cur%10);
            curnode = curnode->next;
            carry = cur/10;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carry){
            curnode->next = new ListNode(carry);
        }
        return dummyHead->next;
    }
};