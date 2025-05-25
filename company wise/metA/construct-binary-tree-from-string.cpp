// 20 may 2025..
// failed..sev0

class Solution {
public:
    TreeNode* str2tree(string s) {
        int idx = 0, n = s.size();
        return helper(s,idx,n);
    }

     bool isDigit(char c){
        return ((c>='0') && (c<='9')) || (c=='-');
     }

    TreeNode* helper(string& s, int& idx, int n){
        if(idx >= n) return nullptr;
        string val = "";
        while(isDigit(s[idx])){
            val.push_back(s[idx++]);
        }
        auto root = new TreeNode(stoi(val));
        if(s[idx] == '(') {
            root->left = helper(s,++idx,n);
            idx++;
        } 
        if(s[idx] == '(') {
            root->right = helper(s,++idx,n);
            idx++;
        } 
        return root;

    }
};

//"4(2(3) (1))(6(5))"

//4(2)