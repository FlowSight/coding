/// Severity: Sev0
// Date: 19Jun26
// LC: 1932
// Where I failed: algo..but i was almost there..root has no parent..
// Pattern: tree..misc
// Notes: additional_notes




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
    unordered_map<int,TreeNode*> mm;
    unordered_map<int,int> valmap;
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        for(auto it : trees) {
            mm[it->val] = it;
            valmap[it->val]++;
            if(it->left) valmap[it->left->val]++;
            if(it->right) valmap[it->right->val]++;
        }
        for(auto it : mm){
            if(valmap[it.first] == 1) return (dfs(it.second) && (mm.size()==1)) ? it.second : nullptr;
        }
        return nullptr;
    }

    bool dfs(TreeNode* root, int left = INT_MIN, int right = INT_MAX){
        if(!root) return true;
        if((root->val <=left) || (root->val >= right)) return false;
        // leaf : 
        /*
         leaf
         same val can be in roots, 
         2 roots cant have same val.
         but watch out for leaf root.
        */
        if(root->left == root->right){
            auto it = mm.find(root->val);
            if(it != mm.end()) {
                if(it->second == root) return true; 
                // no need to replace node, val is same
                root->left = it->second->left;
                root->right = it->second->right;
                mm.erase(it);
            }
        }
        return dfs(root->left,left, root->val) && dfs(root->right,root->val,right);
    }
};


/*

or 
just take those leaves which have matching roots
count unique values, that will be in whole tree after merging
try to merge leafs one by one
validate bst + count total nodes==unique nodes
*/ */






weighted 