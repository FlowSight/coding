// 29 may 2025..
// compiler error silly..

// 30 march 2025
// 14 min 
// didnt care to read the qs..its easy..
// sev3

class Solution {
    public:
        
        vector<vector<int>> verticalTraversal(TreeNode* root) {
            vector<vector<int>> ans;
            map<int,multiset<int>> mm_tmp;
            map<int,vector<int>> mm;
            mm.clear();
            queue<pair<TreeNode*,int>> q;
    
            q.push({root,0});
    
            while(!q.empty()) {
                auto sz = q.size();
                mm_tmp.clear();
                while(sz--){
                    TreeNode* node = q.front().first;
                    int col = q.front().second;
                    q.pop();
                    mm_tmp[col].insert(node->val);
                    if(node->left)q.push({node->left,col-1});
                    if(node->right)q.push({node->right,col+1});
                }
                for(auto it : mm_tmp){
                    for(auto it1: it.second){
                        mm[it.first].push_back(it1);
                    }
                }
            }
    
            for(auto it : mm){
                ans.push_back({});
                for(auto it1: it.second){
                    ans.back().push_back(it1);
                }
            }
            return ans;
        }
    };