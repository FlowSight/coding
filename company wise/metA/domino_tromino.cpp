// 3 june 2025
// did, mod issue. sev2
//just know that with domino and tromino, every 3+ shape can be formed in 2 ways

class Solution {
public:
    int numTilings(int n) {
        int mod = 1e9+7, with3 = 0;
        vector<int> dp(n+1,1);
        for(auto i=2;i<=n;i++){
            dp[i] = ((dp[i-1] + dp[i-2])%mod + (2*with3)%mod)%mod;
            with3 = (with3 + dp[i-2])%mod;
        }
        return dp[n];
    }
};

