/// Severity: Sev0..sev0..sev0..sev0..sev0..sev0
// Date: 22May26
// LC: 2791
// Where I failed: algo
// Pattern: tree dp + palindrome bitmask
// Notes: 
// if a bm so far is mask, ans same mask was found earlier, that means some group of even count chars were in middle..-> palindrome
// if we dont have same mask earlier, but same bm with one odd char is afound earlier, then we have all but one odd freq in current path




class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi g;
    unordered_map<int,int> dp;
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        g = vvi(n,vi());
        for(auto i=1;i<n;i++) g[parent[i]].push_back(i);
        dp[0] = 1;
        return helper(0,0,s);
    }
    long long  helper(int idx, int mask,string& s){
        long long ans = 0;
        if(idx) {
            mask ^= (1<<(s[idx]-'a'));
            for(auto i=1<<25;i;i>>=1){
                if(dp.find(mask ^ i) != dp.end()) {
                    ans += dp[mask ^ i];
                }
            }
            ans += dp[mask];
            dp[mask]++;
        }
        for(auto v:g[idx]){
            ans += helper(v,mask,s);
        }
        return ans;
    }
};
