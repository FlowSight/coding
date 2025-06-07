
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        helper(root,0);
        return root;
    }

    // returns sum of this subtree
    int helper(TreeNode* root, int greaterSum){
        if(!root) return 0;
        auto rr = helper(root->right,greaterSum);
        root->val += greaterSum + rr;
        auto ll = helper(root->left,root->val),
            sum = root->val + ll - greaterSum;
        return sum;
    }
};