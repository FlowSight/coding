// 1 may 2025
// 1 logical mistake..

struct Node {
    public:
    TreeNode* root;
    int min, max;
    Node(TreeNode* _root, int _min, int _max){
        root = _root;
        min = _min;
        max = _max;
    }
 };

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<Node*> st;
        Node* lastPop = nullptr;
        while(!st.empty() || root){
            if(root) {
                st.push(new Node(root,root->val,root->val));
                root = root->left;
            } else {
                root = st.top()->root;
                if(!root->right || (lastPop && (lastPop->root == root->right))) {
                    lastPop = st.top();
                    st.pop();
                    root = nullptr;

                    if(!st.empty()) {
                        if(st.top()->root->left == lastPop->root) {
                            if(lastPop->max >= st.top()->min) return false;

                        } else {
                            if(lastPop->min <= st.top()->max) return false;
                        }
                        st.top()->max = max(st.top()->max,lastPop->max);
                        st.top()->min = min(st.top()->min,lastPop->min);
                    }
                } else {
                    root = root->right;
                }
            }
        }
        return true;
    }
};