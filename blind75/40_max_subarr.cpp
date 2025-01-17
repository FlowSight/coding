
    int maxSubArray(vector<int>& nums) {
        int cur = 0, ans = INT_MIN;
        for(auto it : nums){
            cur+=it;
            ans = max(ans,cur);
            if(cur<0)cur = 0;
        }
        return ans;
    }
    

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return helper(nums, 0,nums.size()-1);
    }

    int helper(vector<int>& nums, int l , int r){
        if(l==r)return nums[l];
        if(l>r)return INT_MIN;

        int mid = (l+r)/2, lSum = 0, lMax = INT_MIN, rSum = 0, rMax = INT_MIN;

        auto ll = helper(nums,l,mid), rr = helper(nums,mid+1,r);
        for(auto i=mid;i>=l;i--){
            lSum += nums[i];
            lMax = max(lMax,lSum);
        }
        for(auto i=mid+1;i<=r;i++){
            rSum += nums[i];
            rMax = max(rMax,rSum);
        }
        return max({ll,rr,lMax+rMax});
    }
};