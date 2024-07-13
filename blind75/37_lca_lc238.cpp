// idea is , result of a node, will contain either the lca, or either of the nodes..   
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
       if(!root || root == p || root == q)return root;
       auto ll = lowestCommonAncestor(root->left,p,q), rr = lowestCommonAncestor(root->right,p,q);
       if(!ll && !rr) return nullptr;
       if(ll && rr)return root;
       return ll ? ll : rr;
   }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> st;
        TreeNode* lastPop = nullptr;
        TreeNode* pPar = p;
        TreeNode* qPar = q;
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                auto cur = st.top();
                if(lastPop == cur->right || !(cur->right)) {

                    // This is the crunch
                    if(cur == pPar || (cur->left == pPar) || (cur->right == pPar)) pPar = cur;
                    if(cur == qPar || (cur->left == qPar) || (cur->right == qPar)) qPar = cur;
                    if((pPar == cur) && (qPar == cur))return cur;


                    lastPop = st.top();
                    st.pop();
                } else {
                    root = st.top()->right;
                }
            }
        }
        return nullptr;
    }
