// 7 nov 2024...took 35 mins..mistake in reverse list...forgot syntax
// got it now...the assigning has to be like ... rhs == next lines lhs
// prev = cur;
// cur = prev;
// way slow...has to be within 15 mins with dry run..

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
    void reorderList(ListNode* head) {
        auto dummyNode = new ListNode();
        dummyNode->next = head;
        int len = 0;
        while(head){
            len++;
            head = head->next;
        }
        int idx = (len-1)/2;
        head = dummyNode->next;
        while(idx){
            head = head->next;
            idx--;
        }
        head->next = reverse(head->next);
        auto l = dummyNode->next; // 1->4
        auto r = head->next;
        auto prev = dummyNode;
        while(r){
            auto rNext = r->next;
            auto lNext = l->next;
            l->next = r;
            prev->next = l;
            prev = r;
            l = lNext;
            r = rNext;
        }
        if(len%2){
            prev->next = l;
            l->next = nullptr;
        }
    }

    ListNode* reverse(ListNode* head){
        ListNode* cur = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        while(cur){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
