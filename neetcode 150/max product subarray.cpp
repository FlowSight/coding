class Solution {
public:
    long mod = 1e11+7;
    int maxProduct(vector<int>& nums) {
        long long mi = nums[0], ma = nums[0], ans = nums[0], n = nums.size();
        for(auto i=1;i<n;i++){
            long long tmp = ma;
            ma = max({nums[i]*ma,nums[i]*mi,(long long)nums[i]});
            mi = min({nums[i]*tmp,nums[i]*mi,(long long)nums[i]});
            ans = max(ans,ma);
            ma = ma%mod;
            mi = mi%mod;
        }
        return ans;
    }
};

