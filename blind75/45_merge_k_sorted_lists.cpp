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
struct cmp {
    bool operator() (const ListNode* node1, const ListNode* node2) const {
        return node1->val < node2->val;
    }
};

class Solution {
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        multiset<ListNode*,cmp> ss;
        int n = lists.size();
        ListNode* dummyNode = new ListNode();
        ListNode* prev = dummyNode;

        for(auto i=0;i<n;i++)if(lists[i])ss.insert(lists[i]);

        while(!ss.empty()) {
            auto tp = *(ss.begin());
            ss.erase(ss.begin());

            prev->next = tp;
            prev = prev->next;
            tp = tp->next;
            if(tp){
                ss.insert(tp);
            }
        }
        return dummyNode->next;
    }
};