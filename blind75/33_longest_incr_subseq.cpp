class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 1;
        vector<int> dp = {nums[0]};

        for(auto i=1;i<n;i++){
            int ub = upper_bound(dp,nums[i]);
            if(ub == -1){
                dp.push_back(nums[i]);
            } else {
                dp[ub] = nums[i];
            }
        }
        return dp.size();
    }

    int upper_bound(vector<int>& dp, int num){
        int l = 0, r = dp.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r)return dp[l]>=num ? l : dp[r] >= num ? r : -1;
            mid = (l+r)/2;
            if(dp[mid] == num)return mid;
            if(dp[mid] > num)r = mid;
            else l = mid+1;
        }
        return dp[l] >= num ? l : -1;
    }
};