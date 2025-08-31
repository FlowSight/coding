// 30 march...was corect
// BUT DIDNT DRY RUN..
// HENCE HAD TO PAY PRICE..13 MINS..
// SEV1


// 27 dec 2024..
// 12 min
// didnt read qs...first coded assuming we need to output the no of removes..
// verdict : FAIL
// SEV0


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


// in place sol

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int total_open = 0, extra_open = 0, n = s.size(), idx = 0, keep = 0, len = 0;
        for(auto c:s) {
            if(c=='('){
                total_open++;
                extra_open++;
                s[idx++] = c;
            } else if(c==')') {
                if(extra_open) {
                    extra_open--;
                    s[idx++] = c;
                }
            } else {
                s[idx++] = c;
            }
        }
        len = idx;
        idx = 0;
        keep = total_open - extra_open;
        for(auto i=0;i<len;i++) {
            auto c = s[i];
            if(c == '(') {
                if(keep) {
                    s[idx++] = c;
                    keep--;
                }
            } else  {
                s[idx++] = c;
            }
        }
        return s.substr(0,idx);
    }
};