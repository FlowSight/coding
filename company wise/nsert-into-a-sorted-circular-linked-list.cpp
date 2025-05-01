// 27 apr 2025
// messed up big time...in implementation and corner cases
// sev0


class Solution {
    public:
        Node* insert(Node* head, int insertVal) {
            if(!head) {
                head = new Node(insertVal);
                head->next = head;
                return head;
            }
            auto dummy = new Node(-9999999);
            dummy->next = head;
            auto prev = head;
            head = head->next;
    
            while((prev->val <= head->val) && (prev != head) && (head != dummy->next)) {
                prev = prev->next;
                head = head->next;
            }
            if((insertVal >= prev->val) || (insertVal <= head->val) ) {
                prev->next = new Node(insertVal);
                prev->next->next = head;
                return dummy->next;
            }
            while ((insertVal < prev->val) || (insertVal > head->val)) {
                head = head->next;
                prev = prev->next;
             }
            prev->next = new Node(insertVal);
            prev->next->next = head;
    
    
            return dummy->next;
        }
    };