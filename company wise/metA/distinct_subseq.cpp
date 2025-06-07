// 6 june 2025..failed in space optimization..sev2

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size(), mod = 1e9+7;
        vvi dp(2,vi(n+1,0));
        dp[0][0] = dp[1][0] = 1; // this line i missed making dp[1][0] = 1...critical
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                dp[1][j] = dp[0][j];
                if(s[i-1] == t[j-1]) dp[1][j] = (dp[1][j] +  dp[0][j-1])%mod;
            }
            dp[0] = dp[1];
        }
        return dp[1][n];

    }
};

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size(), mod = 1e9+7;
        vvi dp(m+1,vi(n+1,0));
        for(auto i=0;i<=m;i++)dp[i][0] = 1;
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=min(i,n);j++){
                dp[i][j] = dp[i-1][j];
                if(s[i-1] == t[j-1]) dp[i][j] = (dp[i][j] +  dp[i-1][j-1])%mod;
            }
        }
        return dp[m][n];

    }
};
