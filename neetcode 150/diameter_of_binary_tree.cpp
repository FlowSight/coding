// 29 apr 2025
// 7 min recursive , 13 min iterative

class Solution {
    public:
        int diameterOfBinaryTree(TreeNode* root) {
            stack<pair<TreeNode*,int>> st;
            TreeNode* lastPop = nullptr;
            pair<TreeNode*,int> tmp;
            int ans = 0;
    
            while(!st.empty() || root){
                if(root) {
                    st.push({root,0});
                    root = root->left;
                } else {
                    tmp = st.top();
                    if(!tmp.first->right || (lastPop == tmp.first->right)) {
                        st.pop();
                        lastPop = tmp.first;
                        root = nullptr;
    
                        if(!st.empty()) {
                            ans = max(ans,st.top().second+tmp.second+1);
                            st.top().second = max(st.top().second,tmp.second+1);
                        }
                    } else {
                        root = tmp.first->right;
                    }
                }
            }
            ans = max(ans,tmp.second);
    
            return ans;
        }
    };
    
    
    //distance from node to node