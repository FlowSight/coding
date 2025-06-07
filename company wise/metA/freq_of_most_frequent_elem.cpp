// 4 june 2025
// great qs..failed..sev0

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        long n = nums.size(), curSum  = 0, l = 0,r = 1, ans = 1;
        sort(nums.begin(),nums.end());
        curSum += nums[0];
        for(;r<n;r++){
            while((r-l)*nums[r] - curSum > k){
                curSum -= nums[l++];
            }
            ans = max(ans,r-l+1);
            curSum += nums[r];
        }
        return ans;
    }
};