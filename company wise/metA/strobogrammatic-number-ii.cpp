// 22 apr 2025
// 1 compiler mistake + 1 corner case..
// 16 mins
// sev0

class Solution {
    public:
        unordered_map<char,char> mm;
        vector<string> findStrobogrammatic(int n) {
            if(n==1) return {"0", "1", "8"};
            string cur(n,'.');
            vector<string> ans = {};
            mm['1'] = '1';
            mm['8'] = '8';
            mm['6'] = '9';
            mm['9'] = '6';
            mm['0'] = '0';
            int idx = 0;
            helper(n,idx,ans,cur);
            return ans;
        }
    
        void helper(int n, int idx, vector<string>& ans, string& cur){
            if(idx >= (n+1)/2) {
                ans.push_back(cur);
                return;
            }
            for(auto it : mm) {
                if((it.first == '0' ) && (idx == 0)) continue;
                if((it.first == '6' ) && (idx == n-1-idx)) continue;
                if((it.first == '9' ) && (idx == n-1-idx)) continue;
                cur[idx] = it.first;
                cur[n-1-idx] = it.second;
                helper(n,idx+1,ans,cur);
            }
        }
    };
    
    
    // n=2
    // ans = {"11","88","69","96"}
    
    // helper(2,1,{}."96")
    // helper(2,0,{}."..")
    
    