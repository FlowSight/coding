class Solution {
public:
    string decodeString(string s) {
        int idx = 0;
        return helper(s,idx);
    }

    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }

    string helper(string& s,int& idx){
        int val = 0;
        string ans = "";
        while(idx<s.size()){
            if(isDigit(s[idx])) {
                val = val*10 + (s[idx++]-'0');
            } else {
                if(s[idx] == ']') break;
                if(s[idx] == '[') {
                    idx++;
                    auto tmp = helper(s,idx);
                    for(auto i=1;i<=val;i++) ans += tmp;
                    idx++;
                } else {
                    ans.push_back(s[idx++]);
                }
                val = 0;
            }
        }
        return ans;
    }
};


//saving [] indexes
    string helper(string& s,int l, int r){
        int val = 0;
        string ans = "";
        for(auto i=l;i<=r;){
            if(s[i] == ']') break;
            if(s[i] == '['){
                auto tmp = helper(s,i+1,mm[i]-1);
                for(auto j=1;j<=val;j++) ans += tmp;
                i = mm[i]+1;
                val = 0;
            } else if(isDigit(s[i])) {
                val = val*10 + (s[i++]-'0');
            } else {
                ans.push_back(s[i++]);
            }
        }
        return ans;
    }


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