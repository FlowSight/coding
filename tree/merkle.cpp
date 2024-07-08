    size_t getMerkleHash(TreeNode* root, int putInMap = 1){
        if(!root || ans)return INT_MAX;
        hash<string> str_hash;
        auto lHash = getMerkleHash(root->left), rHash = getMerkleHash(root->right), rootHash = str_hash(to_string(root->val));
        auto calcHash = str_hash(to_string(lHash)+to_string(rootHash)+to_string(rHash));
        if(putInMap) mm[root->val].insert(calcHash);
        if(target == calcHash)ans = 1;
        return calcHash;
    }