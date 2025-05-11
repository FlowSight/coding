// 5 may 2025..onek tricks ache..i have lost here..

class Solution {
    public:
        int maxProfit(int k, vector<int>& prices) {
            int ans = 0, n = prices.size(), runningMax = 0;
            vector<vector<int>> dp(k+1,vector<int>(n+1,0));
            for(auto i=1;i<=k;i++){
                runningMax = -prices[0];
                for(auto j=2;j<=n;j++) {
                        dp[i][j] = max(dp[i][j-1],runningMax + prices[j-1]);
                        runningMax = max(runningMax,dp[i-1][j-1]-prices[j-1]);
                        ans = max(ans,dp[i][j]);
                }
            }
            return ans;
        }
    };
    