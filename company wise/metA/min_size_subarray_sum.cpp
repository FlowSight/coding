// 1 may 2025..clean..but had to come up with O(n)/O(1) sol
// after seeing sol..didnt see sol..saw that it can be done..

class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            int n = nums.size(), ans = n+1;
            for(auto l=0,leftSum = 0,r=0,cur = 0;r<n;r++){
                cur += nums[r];
                while((l<=r) && cur-leftSum >= target) {
                    ans = min(ans,r-l+1);
                    leftSum += nums[l++];
                }
            }
            return ans == n+1 ? 0 : ans;
        }
    };
    