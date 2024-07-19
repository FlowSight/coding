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
    unordered_map<int,vector<TreeNode*>> dp;
    vector<TreeNode*> allPossibleFBT(int n) {
        dp = unordered_map<int,vector<TreeNode*>>();
        dp[0] = {};
        dp[1] = {new TreeNode(0)};
        return helper(n);
    }
    vector<TreeNode*> helper(int n){
        if(n%2 == 0)return {};
        if(dp.find(n) != dp.end())return dp[n];
        vector<TreeNode*> ans;
        for(auto i=1;i<n-1;i+=2){
            auto ll = helper(i), rr = helper(n-1-i);
            if(ll.size() == 0 || rr.size() == 0)continue;
            for(auto l : ll){
                for(auto r : rr){
                    auto root = new TreeNode(0);
                    root->left = l;
                    root->right = r;
                    ans.push_back(root);
                }
            }
        }
        return dp[n] = ans;
    }
};