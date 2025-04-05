// 14 march 2025
// got the right idea..missed the subset sum 1d calculation approach..
// sev0

class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            int sum = 0, limit = 0;
            for(auto it : nums)sum+=it;
            if(sum%2) return false;
    
            vector<int> dp(sum/2+1,0);
            dp[0] = 1;
    
            for(auto it : nums){
                for(auto i=sum/2; (i-it>=0) && (dp[sum/2] == 0); i--){
                    if(dp[i-it]) {
                        dp[i] = 1;
                    }
                }
            }
            return dp[sum/2];
        }
    };