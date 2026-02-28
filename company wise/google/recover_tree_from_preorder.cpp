/// Severity: Sev2
// Date: 23Feb26
// LC: 1028
// Where I failed: dry run
// Pattern: preorder + stack
// Notes: i got it. but didnt dry run




class Solution {
public:
    TreeNode* recoverFromPreorder(string str) {
        int idx = 0, n= str.size();
        stack<TreeNode*> st;
        TreeNode* ans;
        while(idx < n){
            auto next = getNext(idx,str);
            auto node = new TreeNode(next.second);
            if(st.empty()) {
                st.push(node);
                ans = node;
            }
            else if(st.size() == next.first) {
                if(st.top()->left) st.top()->right = node;
                else st.top()->left = node;
                st.push(node);
            } else {
                while(st.size() != next.first){
                    st.pop();
                }
                if(st.top()->left) st.top()->right = node;
                else st.top()->left = node;
                st.push(node);
            }
        }
        return ans;
    }

    pair<int,int> getNext(int& idx, string& str){
        int depth = 0, val = 0;
        while(str[idx] == '-') {
            idx++;
            depth++;
        }
        while((idx < str.size()) && isDigit(str[idx])) {
            val = val*10 + (str[idx++]-'0');
        }
        return {depth,val};
    }

    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
};