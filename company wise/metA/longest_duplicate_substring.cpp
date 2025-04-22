// 13 apr 2025
// did kmp first..but was not accepted with TLE..
// also did fuck up on what was the ans expected..
// sev0


// rabin karp
class Solution {
    public:
        unordered_map<long,vector<int>> mm;
        vector<long> exp;
        int mod = 1e9+7;
        string longestDupSubstring(string s) {
            int l = 1, n = s.size(), r = n, mid = 0;
            exp = vector<long>(n,1);
            for(auto i=1;i<n;i++){
                exp[i] = (exp[i-1]*256)%mod;
            }
    
            string ans = "", cur = "";
    
            while(l<r){
                if(l+1 == r) {
                    cur =  tryDupSubstr(s,r);
                    if(cur.size()) return cur;
                    return tryDupSubstr(s,l);
                }
                mid = (l+r)/2;
                auto cur = tryDupSubstr(s,mid);
                if(cur.size()) {
                    l = mid;
                    ans = cur;
                } else r = mid-1;
            }
            return ans;
        }
    
        string tryDupSubstr(string& s, int len){
            long hash = 0;
            mm.clear();
            for(auto i=0;i<len;i++){
                hash = (hash*256 + (int)s[i])%mod;
            }
            mm[hash].push_back(0);
            for(auto i=len;i<s.size();i++){
                hash = (hash - (exp[len-1]*s[i-len])%mod + mod) %mod;
    
                hash = ((hash*256)%mod + (int)s[i])%mod;
                
                if(mm.find(hash) != mm.end()) {
                    auto cur = s.substr(i-len+1,len);
                    for(auto it : mm[hash]) {
                        auto candidate = s.substr(it,len);
                        if( cur == candidate) return cur;
                    }
                }
                mm[hash].push_back(i-len+1);
            }
            return "";
        }
    };


// kmp
class Solution {
    public:
        vector<int> lps;
        string longestDupSubstring(string s) {
            int ans = 0, n = s.size(), idx = 0;
            lps = vector<int>(n,0);
            for(auto i=0;i<n;i++){
                auto len = kmp(s,i);
                if(len > ans) {
                    idx = i;
                    ans = len;
                }
            }
            return s.substr(idx,ans);
        }
    
        int kmp(string& s, int& start){
            int n = s.size()-start, idx = 0, ans = 0;
            for(auto i=1;i<n;i++){
                lps[i] = 0;
                while(idx && (s[idx+start] != s[i+start])) idx = lps[idx-1];
                idx += (s[idx+start] == s[i+start]);
                ans = max(ans,idx);
            }
            return ans;
        }
    };
