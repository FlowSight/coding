//29jan26..horribly beaten...sev0..sev0..sev0..sev0

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    int countPalindromicSubsequences(string s) {
        int n = s.size(), mod = 1e9+7, ans = 0;
        vvvi dp(n,vvi(n,vi(4,0)));
        for(auto len = 1;len<=n;len++){
            for(auto i=0;(i+len-1<n);i++){
                int j = i+len-1;
                if(len == 1) {
                    dp[i][i][s[i]-'a'] = 1;
                    continue;
                }
                if(s[i] != s[j]) {
                    for(auto c='a';c<='d';c++) dp[i][j][c-'a'] = (dp[i+1][j][c-'a'] + dp[i][j-1][c-'a'] - dp[i+1][j-1][c-'a']+mod)%mod;
                } else {
                    for(auto c='a';c<='d';c++){
                        dp[i][j][s[i]-'a'] = (dp[i][j][s[i]-'a'] + (dp[i+1][j-1][c-'a'])%mod)%mod;
                        if(c!=s[i]) dp[i][j][c-'a'] = (dp[i+1][j][c-'a'] + dp[i][j-1][c-'a'] - dp[i+1][j-1][c-'a']+mod)%mod;
                    }
                    dp[i][j][s[i]-'a'] = (dp[i][j][s[i]-'a'] + 2)%mod;
                }
            }
        }
        for(auto i=0;i<4;i++)ans = (ans + dp[0][n-1][i])%mod;
        return ans;
    }
};
