/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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