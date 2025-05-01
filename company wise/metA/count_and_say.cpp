//23 apr 2025
// // 22 apr 2025..8.3 min..clean

class Solution {
    public:
        string countAndSay(int n) {
            if(n==1) return "1";
            string last = "1";
            for(auto i=2;i<=n;i++){
                last = getRLE(last);
            }
            return last;
        }
    
        string getRLE(string& s){
            int n = s.size();
            string ans = "";
            for(auto i=0,cnt = 1;i<n;i++,cnt = 1){
                while((i+1<n) && (s[i] == s[i+1])) {
                    cnt++;
                    i++;
                }
                auto tmp = to_string(cnt);
                for(auto &c : tmp)ans.push_back(c);
                ans.push_back(s[i]);
            }
            return ans;
        }
    };
    
