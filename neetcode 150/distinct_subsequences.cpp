// 20 feb 25
// missed base case..
// then went onto a wrong path..but initial dp state was correct..
// sev0
// write down the meaning of the dp state and TRULY UNDERSTAND it..

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size(), ans = 0, mod = 1e9+7;
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        for(auto i=0;i<=m;i++)dp[i][0] = 1;
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                dp[i][j] =  (dp[i-1][j] + (s[i-1] == t[j-1] ? dp[i-1][j-1] :0)) % mod;
            }
        }
        return dp[m][n];
    }
};
