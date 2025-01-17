

//  15 dec 2024..15 min..
//   forgot..but was on track later..but made a silly mistake later..
//   also made a mistake in returning..didnt dry run
//   verdict : FAIL

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* lastPop = nullptr;
        while(!st.empty() || root) {
            if(root) {
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                if(!root->right || (lastPop == root->right)) {
                    auto tmp = root->right;
                    root->right = root->left;
                    root->left = tmp;
                    
                    st.pop();
                    lastPop = root;
                    root = nullptr;
                } else {
                    root = root->right;
                }
            }
        }
        return lastPop;
    }
};


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