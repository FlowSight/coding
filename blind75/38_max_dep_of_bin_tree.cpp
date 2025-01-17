// 15 dec 2024..5 min..bujhte parini je inorder e hobe na...
// verdict : FAIL
    int maxDepth(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* lastPop = nullptr;
        int ans = 0;
        while(!st.empty() || root){
            if(root) {
                st.push(root);
                root = root->left;
                ans = max(ans,(int)st.size());
            } else {
                root = st.top();
                if(root->right && (lastPop != root->right)) {
                    root = root->right;
                } else {
                    lastPop = st.top();
                    st.pop();
                    root = nullptr;
                }
            }
        }
        return ans;
    }


class Solution {
public:
    int maxDepth(TreeNode* root,int depth = 0) {
        if(!root)return depth;
        return max(maxDepth(root->left,depth+1),maxDepth(root->right,depth+1));
    }
};