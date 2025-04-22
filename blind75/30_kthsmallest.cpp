
 //16 dec 2024...2 min..no mistake..Verdict : PASS

    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        while(!st.empty() || root) {
            if(root) {
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                st.pop();
                if(k-- == 1){
                    return root->val;
                }
                root = root->right;
            }
        }
        return -1;
    }


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

// stephan pochman did some shit
// sev0
int kthSmallest(TreeNode* root, int k) {
    vector<TreeNode*> stac(k);
    int i = 0, j = k;
    while (true) {
        while (root) {
            stac[i++%k] = root;
            root = root->left;
        }
        root = stac[--i%k];
        if (! --j)
            return root->val;
        root = root->right;
    }
}

// followup : insert/delete/modify happening. how to optimize kthsmallest if called frequently:
// ans : save left and right subtree count in each node, do a optimized binary search..log(h)