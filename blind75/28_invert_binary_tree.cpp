/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> st;
        auto orig = root;
        TreeNode* lastPop = nullptr;
        while(!st.empty() || root){
            if(root){
                st.push(root);
                root = root->left;
            } else {
                if(lastPop == st.top()->right || !st.top()->right){
                    auto ll = st.top()->left;
                    st.top()->left = st.top()->right;
                    st.top()->right = ll;
                    lastPop = st.top();
                    st.pop();
                } else {
                    root = st.top()->right;
                }
            }
        }
        return orig;

    }
};