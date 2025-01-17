// 14 jan 2025 
20 mins..
logical error .. didnt see index not being set properly..
did only n^2 approach..
    string decodeString(string s) {
        return decodeHelper(s,0);
    }

    string decodeHelper(string& s, int idx){
        int n = s.size(), cnt = 0;
        string ans = "";
        for(auto i=idx;i<n;i++){
            if((s[i]>='0') && (s[i]<='9')){
                cnt = cnt*10+s[i]-'0';
            } else {
                if(cnt == 0)ans.push_back(s[i]);
                else {
                    auto tmp = helper(s,i);
                    auto res = decodeHelper(tmp,0);
                    for(auto j=1;j<=cnt;j++){
                        for(auto c: res){
                            ans.push_back(c);
                        }
                    }
                    cnt = 0;
                }
            }
        }
        return ans;
    }

    string helper(string& s, int& idx){
        int n = s.size(), cnt = 0, start = idx;
        string ans = "";
        for(;idx<n;idx++){
            if(s[idx]=='[')cnt++;
            else if(s[idx]==']')cnt--;
            if(cnt == 0) {
                return s.substr(start+1,idx-start-1);
            } 
        }
        return ans;
    }


// better stack approach

class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        string ans = "", cnt = "";
        for(auto c : s){
            if(c=='['){
                st.push(ans);
                st.push(cnt);
                ans = "";
                cnt = "";
            }
            else if(c==']'){
                auto repeat = stoi(st.top());
                st.pop();
                auto prevStr = st.top();
                st.pop();
                auto tmp = "";
                for(auto i=1;i<=repeat;i++){
                    for(auto &ch :  ans) prevStr.push_back(ch);
                }
                ans = prevStr;
            } else if((c>='a') && (c<='z')){
                ans.push_back(c);
            } else {
                cnt.push_back(c);
            }
        }
        return ans;
    }
};

// theres one more recursive O(n) way // TODO