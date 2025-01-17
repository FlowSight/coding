// 27 dec 2024..
// 12 min
// didnt read qs...first coded assuming we need to output the no of removes..
// verdict : FAIL


// 22 dec 2024...8 min..
// compiler error : 1
// verdict : FAIL

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> st;
        string ans = "";
        int n = s.size();
        for(auto i=0;i<n;i++) {
            if(s[i]>='a' && s[i]<='z')continue;
            if((st.size()>0) && (s[st.back()] == '(') && (s[i]==')')) st.pop_back();
            else st.push_back(i);       
        }
        for(auto i=0,idx=0;i<n;i++){
            if(s[i]>='a' && s[i]<='z') {
                ans.push_back(s[i]);
            } else {
                if(idx<st.size() && st[idx] == i) {
                    idx++;
                    continue;
                } else {
                     ans.push_back(s[i]);
                }
            }
        }
        return ans;
    }
};

