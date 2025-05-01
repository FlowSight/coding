// 25 apr 2025
// 12 min..clean


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