// 28 may 2025
// silly mistake while returning..sev0

// 27 apr 2025..no error
//11 nov..2024..8 mins..dry run..no  error
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        n--;
        ListNode* dummyNode = new ListNode();
        dummyNode->next = head;
        ListNode* cur = dummyNode;
        while(n){
            head = head->next;
            n--;
        }
        while(head->next){
            head = head->next;
            cur = cur->next;
        }
        cur->next = cur->next->next;
        return dummyNode->next;
    }


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto dummynode = new ListNode();
        dummynode->next = head;
        auto l = dummynode;
        auto r = dummynode;
        while(n--){
            r = r->next;
        }
        while(r->next){
            l = l->next;
            r = r->next;
        }
        l->next = l->next->next;
        return dummynode->next;
    }
};