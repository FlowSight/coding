class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        dp[0][0] = 1;
        for(auto i=0;i<n;i++){
            if(p[i]!='*') break;
            dp[0][i+1] = 1;
        }
        for(auto i=1;i<=m;i++){
             for(auto j=1;j<=n;j++){
                if(p[j-1] == '*') {
                    dp[i][j] = dp[i][j-1] || (dp[i-1][j] ) || 
                        dp[i-1][j-1];
                } else {
                    if((p[j-1] == '?') || (s[i-1] == p[j-1])) dp[i][j] = dp[i-1][j-1];
                }
             }
         }
        return dp[m][n];
    }
};