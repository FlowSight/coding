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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>>  ans;
        if(!root)return ans;
        q.push(root);
        while(!q.empty()){
            auto sz = q.size();
            vector<int> cur;
            while(sz--){
                auto tp = q.front();
                q.pop();
                cur.push_back(tp->val);
                if(tp->left)q.push(tp->left);
                if(tp->right)q.push(tp->right);
            }
            ans.push_back(cur);
        }
        return ans;
        
    }
};