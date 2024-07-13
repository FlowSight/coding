
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                if(--k == 0)return root->val;
                st.pop();
                root = root->right;
            }
        }
        return root?root->val:-1;
        
    }
};


