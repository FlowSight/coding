// 2 apr 2025..
// missed corner case of sentinel value of node..
// sev2..
// 4 min

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
    int ans;
    int sentinel = -1e8;
    int maxPathSum(TreeNode* root) {
        ans = sentinel;
        helper(root);
        return ans;
    }

    int helper(TreeNode* root){
        if(!root)return sentinel;
        auto ll = helper(root->left), rr = helper(root->right),
            uptoRoot = max(root->val,root->val + max(ll,rr)),
            throughRoot = root->val + (ll == sentinel ? 0 : ll) + (rr == sentinel ? 0 : rr);
        ans = max({ans,uptoRoot,throughRoot});
        return uptoRoot;
    }
};