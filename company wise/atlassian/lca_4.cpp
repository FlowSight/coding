
// 26oct25 sev0

class Solution {
public:
        unordered_map<int,unordered_set<TreeNode*>> depthMap;
        unordered_map<TreeNode*,TreeNode*> parMap;
        unordered_set<TreeNode*> seen;
        int maxDep;
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        maxDep = 0;
        for(auto it : nodes)seen.insert(it);
        int depth = 0;
        dfs(root,depth);
        
        while((depthMap.size() > 1 ) || (depthMap[maxDep].size()>1)) {
            for(auto it : depthMap[maxDep]){
                depthMap[maxDep-1].insert(parMap[it]);
            }
            depthMap.erase(maxDep--);
        }
        return *(depthMap[maxDep].begin());
    }

    void dfs(TreeNode* root, int& depth){
        if(seen.find(root) != seen.end()) {
            depthMap[depth].insert(root);
            maxDep = max(maxDep,depth);
        }
        if(root->left){
            depth++;
            parMap[root->left] = root;
            dfs(root->left,depth);
            depth--;
        }
        if(root->right){
            depth++;
            parMap[root->right] = root;
            dfs(root->right,depth);
            depth--;
        }
    }
};



// iteraive: make dfs stack based


// clean
TreeNode *res = nullptr;
int traverse(TreeNode* r, unordered_set<TreeNode*> &ns) {
    int match = r == nullptr ? 0 :
        ns.count(r) + traverse(r->left, ns) + traverse(r->right, ns);
    if (match == ns.size() && res == nullptr)
        res = r;
    return match;
}    
TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
    unordered_set<TreeNode*> ns(begin(nodes), end(nodes));
    traverse(root, ns);
    return res;
}  
