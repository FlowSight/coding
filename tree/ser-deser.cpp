#include <cstddef>
#include <string>

using namespace std;

class Codec {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
public:

    // Encodes a tree to a single string.
    string nullStr = "$", sep = ";";
    string serialize(TreeNode* root) {
        if(!root)return nullStr+sep;
        auto ll = serialize(root->left), rr = serialize(root->right);
        return to_string(root->val)+sep+ll+rr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int n = data.size();
        vector<string> arr;
        string tmp = "";
        for(auto i=0;i<n;i++){
            if(data[i] == sep[0]){
                arr.push_back(tmp);
                tmp = "";
            } else {
                tmp.push_back(data[i]);
            }
        }
        int idx = 0;
        return deserialize(arr,idx);
    }
    TreeNode* deserialize(vector<string>& arr, int& l) {
        if(l == arr.size())return nullptr;
        auto root = (arr[l] == nullStr ? nullptr : new TreeNode(stoi(arr[l])));
        l++;
        if(!root)return root;
        auto ll = deserialize(arr,l), rr = deserialize(arr,l);
        root->left = ll;
        root->right = rr;
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));