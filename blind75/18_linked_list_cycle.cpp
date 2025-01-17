
// 5 nov 2024
// missed edge case...was talking in call
    bool hasCycle(ListNode *head) {
        ListNode* dummyNode = new ListNode();
        ListNode* slow = head;
        ListNode* fast = head;
        while(slow && fast){
            slow = slow->next;
            fast = fast->next;
            if(fast) fast = fast->next;
            if(slow && fast && slow==fast)return true;
        }
        return false;
    }


class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(slow->next && fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)return true;
        }
        return false;
    }
};