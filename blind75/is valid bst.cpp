    bool isValidBST(TreeNode* root) { // just genious : last popped, will be either current's left subtree's largest node, OR current is in right subtree of last popped
        stack<TreeNode*> st;
        long last = LONG_MIN; // 0: smaller 1: bigger expected
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                if(last >= root->val)return false;
                st.pop();
                last = root->val;
                root = root->right;
            }
        }
        return true;
    }