// 17/2/25
// 7 mins. for o(n^2( space)
// 5 mins for O(n) space..+ 1 compiler error 
// sev3

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int longestCommonSubsequence(string str1, string str2) {
        int m = str1.size(), n = str2.size(), dp0j = 0, dp0j_1 = 0, dp1j_1 = 0, dpj = 0;
        vvi dp(2,vi(n+1,0));
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                if(str1[i-1] == str2[j-1]){
                    dp[1][j] = dp[0][j-1]+1;
                } else {
                    dp[1][j] = max(dp[1][j-1],dp[0][j]);
                }
                dp[0][j-1] = dp[1][j-1];
            }
            dp[0][n] = dp[1][n];
        }
        return dp[1][n];
    }
};


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vvi dp(2,vi(n+1,0));
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                dp[1][j] = max(dp[1][j-1],dp[0][j]);
                if(s1[i-1] == s2[j-1]) dp[1][j] = max(dp[1][j],dp[0][j-1]+1);
            }
            dp[0] = dp[1];
        }
        return dp[1][n];
    }
};

