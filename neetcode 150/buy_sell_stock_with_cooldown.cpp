// 25 feb 25
// 8 min for n^2..
// 7 min for O(n)
// 1 compiler error..
// sev2

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+1,{0,0});
        dp[1] = {-prices[0],0};
        for(auto i=2;i<=n;i++){
            dp[i][0] = max(dp[i-1][0],-prices[i-1]+dp[i-2][1]);
            dp[i][1] = max(dp[i-1][1],prices[i-1]+dp[i-1][0]);
        }
        return dp[n][1];
    }
};