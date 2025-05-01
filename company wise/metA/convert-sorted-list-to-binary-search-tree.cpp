// 1 may 2025
// 2 compiler mistake + 1 logical mistake..
// sev3

class Solution {
    public:
        TreeNode* sortedListToBST(ListNode* head) {
            return makeTree(head);
        }
        TreeNode* makeTree(ListNode* head) {
            if(!head) return nullptr;
            if(!head->next) return new TreeNode(head->val);
            auto midPrev = findMid(head);
            ListNode* mid = midPrev ? midPrev->next : head; // root
            auto next = mid->next; // start of next half
    
            if(midPrev) midPrev->next = nullptr;
            mid->next = nullptr;
    
            auto root = new TreeNode(mid->val);
            root->left = makeTree(midPrev ? head : midPrev);
            root->right =  makeTree(next);
            return root;
        }
    
        ListNode* findMid(ListNode* node){
            if(!node || !node->next) return node;
            auto slow = node;
            auto fast = node;
            ListNode* prev = nullptr;
            // slow willl stop at mid, prev at just before slow i.e. mid
            while(slow && fast && slow->next && fast->next && fast->next->next){
                prev = slow;
                slow = slow->next;
                fast = fast->next->next;
            } 
            return prev;
        }
        
    };
    
    
