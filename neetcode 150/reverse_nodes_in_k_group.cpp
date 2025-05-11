// 7 may 2025..
// 1 logical mistake..
// sev2

// 14 mar 2025
// 26 mins..
// 2 compiler mistakes
// 1 logical mistake..due to not dry running
// sev1

class Solution {
    public:
        ListNode* reverseKGroup(ListNode* head, int k) {
            auto dummy = new ListNode();
            auto prev = dummy;
            dummy->next = head;
            while(head) {
                auto cur = maybeReverse(head,k); // pair of (head,last) (2,1)
                prev->next = cur.first;
                prev = cur.second;
                head = prev->next;
            }
            return dummy->next;
        }
    
        pair<ListNode*, ListNode*> maybeReverse(ListNode* head, int k){
            auto tmp = head;
            ListNode* next = nullptr;
            while((k>1) && tmp->next){
                k--;
                tmp = tmp->next;
            }
            next = tmp->next;
            if(k==1){
                tmp->next = nullptr;
                tmp = reverse(head);
                head->next = next;
            }
            return k == 1 ? make_pair(tmp,head) : make_pair(head,tmp);
        }
    
        ListNode* reverse(ListNode* head){
            auto dummy = new ListNode();
            ListNode* next = nullptr;
            auto cur = head;
            auto prev = dummy;
            while(cur){
                next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }
            return prev;
        }
    
    };
