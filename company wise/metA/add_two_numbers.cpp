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