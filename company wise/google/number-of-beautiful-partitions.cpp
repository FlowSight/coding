
// Severity: Sev2
// Date: 19Feb26
// LC: 2478
// Where I failed: implementation..time
// Pattern: dp
// Notes: TODO


class Solution {
public:
    int beautifulPartitions(string s, int k, int minLength) {
        string primes = "2357";
        int n = s.size(), mod = 1e9+7;
        if(minLength == 1)minLength++;
        vector<int> dp1(n+1,0),dp2(n+1,0);
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        dp1[0] = (primes.find(s[0]) != string::npos);
        for(auto i=1;i<=n;i++)dp1[i] = dp1[i-1];
        for(auto i=1;i<=k;i++){
            for(auto j=1;j<=n;j++){
                dp2[j] = dp2[j-1];
                if(j<minLength) continue;
                // if prime,cant end
                 if(primes.find(s[j-1]) != string::npos) continue;
                 dp[j][i] = dp1[j-minLength];
                 if((j+1<=n) && (primes.find(s[j]) != string::npos)) {
                    dp2[j] = (dp2[j] + dp[j][i])%mod;
                 }
            }
            dp1 = dp2;
        }
        return dp[n][k];
    }
};
