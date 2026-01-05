// 30/12/25..failed..sev0

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<long> dp(amount+1,0);
        dp[0] = 1;
        long mod = 1e11+7;
        for(auto it : coins){
            for(auto i=it;i<=amount;i++) dp[i] = (dp[i] +  dp[i-it])%mod;
        }
        return dp[amount];
    }
};