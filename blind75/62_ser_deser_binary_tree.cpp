/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    char sep = ';', nullnode = '$';
    string serialize(TreeNode* root) {
        string str = "";
        serialzeHelper(root,str);
        return str;
    }

    void serialzeHelper(TreeNode* root, string& str){
        if(!root){
            str.push_back(sep);
            str.push_back(nullnode);
            return;
        }
        str.push_back(sep);
        auto rootStr = to_string(root->val);
        for(auto c : rootStr){
            str.push_back(c);
        }
        serialzeHelper(root->left,str);
        serialzeHelper(root->right,str);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        return deserializeHelper(data,idx);
    }

    TreeNode* deserializeHelper(string& data, int& idx) {
        if(idx >= data.size())return nullptr;
        idx++; //skip the sep
        if(data[idx] == nullnode){
            idx++;
            return nullptr;
        }
        string rootVal = "";
        while(data[idx] != sep)rootVal.push_back(data[idx++]);
        TreeNode* root = new TreeNode(stoi(rootVal));
        root->left = deserializeHelper(data,idx);
        root->right = deserializeHelper(data,idx);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));