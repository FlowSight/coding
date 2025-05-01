// 29 apr 2025..
// 1 compilation error..8 mins..better ..sev3

// 12 jan 2025..
// 15 mins
// made logical mistake of while condition : didnt recheck code...
// verdict : FAIL

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> st, pPath = {}, qPath = {};
        TreeNode* lastPop = nullptr;
        while(((st.size()>0) || root) && ((pPath.size() == 0) || (qPath.size()==0))) {
            if(root){
                st.push_back(root); // comment : dont check parent while putting to stack..check while popping
                if(root == p){
                    pPath = st;
                }
                else if(root == q){
                    qPath = st;
                }
                root = root->left;
            } else {
                auto cur = st.back();
                if(!cur->right || (lastPop == cur->right)){
                    st.pop_back();
                    lastPop = cur;
                } else {
                    root = cur->right;
                }
            }
        }
        for(auto i=0;(i<pPath.size()) && (i<qPath.size()); i++){
            if(pPath[i] != qPath[i])return pPath[i-1];
        }
        return pPath.size() < qPath.size() ? pPath.back() : qPath.back();
    }



// 16 dec 2024..failed basic vector compile isssues...didnt dry run code..
// verdict  : FAIL
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> pPath = {nullptr}, qPath = {nullptr}, st = {};
        TreeNode* lastPop = nullptr;
        while((st.size() || root) && (!pPath.back()  || !qPath.back())) {
            if(root) {
                st.push_back(root);
                root = root->left;
            } else {
                root = st.back();
                if(root->right && (lastPop != root->right)) {
                    root = root->right;
                } else {
                    if (root == p) {
                        pPath = st;
                    } else if (root == q) {
                        qPath = st;
                    }
                    st.pop_back();
                    lastPop = root;
                    root = nullptr;
                }
            }
        }
        return findCommonLength(pPath,qPath);
    }

    TreeNode* findCommonLength(vector<TreeNode*> arr1, vector<TreeNode*> arr2) {
        int n = min(arr1.size(),arr2.size());
        for(auto i=n-1;i>=0;i--){
            if(arr1[i] == arr2[i]) return arr1[i];
        }
        return arr1[0];
    }





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
