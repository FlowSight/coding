// 26 apr 2025
// stupid mistake..didnt check return type. 
// sev3


class BSTIterator {
    public:
        TreeNode* root;
        stack<TreeNode*> st;
        BSTIterator(TreeNode* _root) {
            root = _root;
            while(root){
                st.push(root);
                root = root->left;
            }
        }
        
        int next() {
            TreeNode* ans = nullptr;
            while(!st.empty() || root) {
                if(root){
                    st.push(root);
                    root = root->left;
                } else {
                    root = st.top()->right;
                    ans = st.top();
                    st.pop();
                    break;
                }
            }
            return ans->val;
        }
        
        bool hasNext() {
            return !st.empty() || root;
        }
    };
    
    // ans = 9
    // root = na
    // {15}
    