// 31 may 2025..
// sev0

// 20 may 2025..
// failed..sev0



class Solution {
    public:
        TreeNode* str2tree(string s) {
            vector<TreeNode*> st;
            int n = s.size();
            for(auto i=0,val = 0, sign = 1;i<n;i++,val = 0,sign = 1){
                if(s[i] == ')') {
                    st.pop_back();
                } else if(s[i] == '(') continue;
                else {
                    if(s[i] == '-') {
                        sign = -1;
                        i++;
                    }
                    while((i<n) && (isDigit(s[i]))){
                        val = val*10 + (s[i] - '0');
                        i++;
                    }
                    val = val*sign;
                    auto node = new TreeNode(val);
                    if(!st.empty()){
                        if(st.back()->left) st.back()->right = node;
                        else st.back()->left = node;
                    }
                    st.push_back(node);
                    i--;
                }
            }
            return st.empty() ? nullptr : st.back();
        }
    
        bool isDigit(char c){
            return (c>='0') && (c<='9');
        }
    };


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