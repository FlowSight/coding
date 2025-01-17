//  7 jan 2025
// 4 mins
// logic error : didnt check node null condition
// verdict : FAIL

    vector<int> rightSideView(TreeNode* root) {
        deque<TreeNode*> q;
        vector<int> ans;
        if(root) q.push_back(root);

        while(!q.empty()) {
            int sz = q.size();
            while(sz--){
                auto cur = q.front();
                q.pop_front();
                if(cur->left)q.push_back(cur->left);
                if(cur->right)q.push_back(cur->right);
                if(sz == 0){
                    // last element
                    ans.push_back(cur->val);
                }
            }
        }
        return ans;
    }
};