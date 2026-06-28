/// Severity: 
// Date: 28Jun26
// LC: 1948
// Where I failed:  thoght leafs also can be dupe, thought intemediate folders (if not given in input arr) will not be require in 
// final ans arr
// Pattern: trie + serialization / hashing

struct treenode {
    public:
    string val;
    treenode* par;
    bool del;
    map<string,treenode*> children;
    treenode(string _v, treenode* _par = nullptr){
        val = _v;
        par = _par;
        del = false;
    }
    treenode() = default;
};

class Solution {
public:
    unordered_map<string,treenode*> dupemap;
    vector<vector<string>> ans;
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        int n = paths.size();
        auto root = new treenode("root");
        for(auto i=0;i<n;i++){
            auto tmp = root;
            for(auto j=0;j<paths[i].size();j++){
                auto key = paths[i][j];
                if(tmp->children.find(key) == tmp->children.end()) {
                    auto node = new treenode(key,tmp);
                    tmp->children[key] = node;
                }
                tmp = tmp->children[key];
            }
        }
        helper(root);
        vector<string> cur = {};
        for(auto it : root->children) {
            fillans(it.second,cur);
        }
        return ans;
    }

    void fillans(treenode* root, vector<string>& cur){
        if(!root) return;
        if(root->del) return;
        cur.push_back(root->val);
        ans.push_back(cur);
        for(auto it : root->children){
            fillans(it.second,cur);
        }
        cur.pop_back();
    }

    string helper(treenode* root){
        if(!root) return "";
        string childrenhash = "";
        for(auto it : root->children) childrenhash += helper(it.second);
        if(childrenhash.size()) {
            if(dupemap.count(childrenhash)){
                root->del = dupemap[childrenhash]->del =  true;
            } else {
                dupemap[childrenhash] = root;
            }
        }
        return "(" + root->val + childrenhash + ")";
    }
};
