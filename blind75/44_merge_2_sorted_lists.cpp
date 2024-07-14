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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        auto dummyNode = new ListNode();
        auto prev = dummyNode;
        while(list1 && list2){
            if(list1->val < list2->val){
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        while(list1){
            prev->next = list1;
            list1 = list1->next;
            prev = prev->next;
        }
        while(list2){
            prev->next = list2;
            list2 = list2->next;
            prev = prev->next;
        }
        return dummyNode->next;
    }
};