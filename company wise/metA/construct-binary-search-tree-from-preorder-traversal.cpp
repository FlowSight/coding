// this is a good qs..did it clean

class Solution {
    public:
        TreeNode* bstFromPreorder(vector<int>& preorder) {
            int idx = 0;
            return helper(preorder,idx,INT_MAX);
        }
    
        TreeNode* helper(vector<int>& preorder,int& idx, int limit){
            if((idx >= preorder.size()) || (preorder[idx] > limit)) return nullptr;
            auto root = new TreeNode(preorder[idx++]);
            root->left = helper(preorder,idx,root->val);
            root->right = helper(preorder,idx,limit);
            return root;
        }
    };
    