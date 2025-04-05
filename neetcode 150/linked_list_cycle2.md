// 13 feb 2025
// couldnt think of O(1) space + O(n) + immutable list sol..
// sev0
// verdict : FAIL

![alt text](./linked_list_cycle.png)
```
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(slow && fast) {
            slow = slow->next;
            if(fast) fast = fast->next;
            if(fast)fast = fast->next;
            if(slow == fast)break;
        }
        if(!fast) return nullptr;
        fast = head;
        while(fast != slow){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
```