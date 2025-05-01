// 26 apr 2025
// missed one corner case + 1 compiler error 
// sev2

class Solution {
    public:
        ListNode* sortList(ListNode* head) {
            return sortHelper(head);
        }
    
        ListNode* sortHelper(ListNode* head){
            if(!head || !head->next) return head;
    
            auto dummyNode = new ListNode();
            dummyNode->next = head;
            auto slow = head;
            auto fast = head;
            while(slow && fast && slow->next && fast->next && fast->next->next){
                slow = slow->next;
                fast = fast->next->next;
            }
            auto head2 = slow->next;
            slow->next = nullptr;
            auto ll = sortHelper(head);
            auto rr = sortHelper(head2);
    
            return merge(ll,rr);
        }
    
        ListNode* merge(ListNode* head1, ListNode* head2){
            if(!head1 && !head2) return nullptr;
            if(!head1) return head2;
            if(!head2) return head1;
    
            auto dummyNode = new ListNode();
            auto prev = dummyNode;
            while(head1 && head2){
                if(head1->val < head2->val) {
                    prev->next = head1;
                    head1 = head1->next;
                } else {
                    prev->next = head2;
                    head2 = head2->next;
                }
                prev = prev->next;
            }
    
            if(head1) prev->next = head1;
            if(head2) prev->next = head2;
    
            return dummyNode->next;
        }
        
    };
    
    // d->-1->0->3->4->5*       
    // s/f
    //    s f
    //      s.  f
    // head2 = 4
    // ll = -1
    // rr = 0