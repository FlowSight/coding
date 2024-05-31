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
        unordered_map<TreeNode*, TreeNode*> mm;
        TreeNode* lastPop = nullptr;
        while(!st.empty() || root){
            if(root){
                if(root == p){
                    if(mm.find(q) != mm.end())return mm[q];
                    mm[p] = p;
                }
                 if(root == q){
                    if(mm.find(p) != mm.end())return mm[p];
                    mm[q] = q;
                }
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                if((mm.find(p) != mm.end()) && ((root->left == mm[p]) || (root->right == mm[p])))mm[p] = root;
                if((mm.find(q) != mm.end()) && ((root->left == mm[q]) || (root->right == mm[q]))) mm[q] = root;
                if((root->right) && (root->right != lastPop)){
                    root = root->right;
                } else {
                    lastPop = root;
                    root = nullptr;
                    st.pop();
                }
            }
        }
        return root;
    }