// 15 dec 2024...7.30 mins...2 compiler mistake..verdict : FAIL
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        return max(robLimit(nums,0,n-2), robLimit(nums,1,n-1));
    }

    int robLimit(vector<int>& nums, int l, int r) {
        if(l>r) return 0;
        if(l==r)return nums[l];
        int n = nums.size(), cur = 0, prev = 0, tmp = 0;
        //vector<int> dp(n,0);
        for(auto i=l;i<=r;i++){
            tmp = cur;
            cur = max(nums[i]+prev,cur);
            prev = tmp;
        }
        return cur;
    }
};




class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)return nums[0];
        return max(robNoCircle(nums,0,n-2),robNoCircle(nums,1,n-1));
    }
    int robNoCircle(vector<int>& nums,int l , int r){
        if(l>r)return 0;
        int dp0 = 0, dp1 = nums[l], dp2 = 0;
        for(auto i=l+1;i<=r;i++){
            dp2 = max(dp1, nums[i]+dp0);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp1;
    }
};

