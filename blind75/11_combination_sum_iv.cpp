class Solution {
public:
    long mod = 1e11+7;
    int combinationSum4(vector<int>& nums, int target) {
        vector<long> dp(target+1,0);
        int n = nums.size();
        sort(nums.begin(),nums.end());
        dp[0] = 1;
        for(auto i=1;i<=target;i++){
            for(auto j=0;j<n;j++){
                if(i<nums[j]) break;
                dp[i] = (dp[i] +dp[i-nums[j]])%mod;
            }
        }
        return dp[target];
    }
};

// dp[i] = (dp[i]+dp[i-nums[j]])