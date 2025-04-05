// 16 mar 2025
// humilation.. beaten
// sev0 sev0
class Solution {
    public:
        Node* copyRandomList(Node* head) {
            if(!head) return nullptr;
            Node* dummy = new Node(-1);
            dummy->next = head;
            auto tmp = head;
            auto  next = head->next;
            while(tmp){
                next = tmp->next;
                tmp->next = new Node(tmp->val);
                tmp->next->next = next;
                tmp = next;
            }
            tmp = head;
            while(tmp){
                if(tmp->random) {
                    tmp->next->random = tmp->random->next;
                }
                tmp = tmp->next->next;
            }
    
            dummy->next = head->next;
            tmp = head;
    
            while(tmp) {
                auto copy = tmp->next;
                next = copy->next;
                tmp->next = next;
                if(next) {
                    copy->next = next->next;
                }
                tmp = tmp->next;
            }
    
            return dummy->next;
        }
    };
    // this is what it looks like after first loop
    //    7->13->11->10->1
    //    |
    //    v
    //    7*->13   13*->11*->10*->1*
    