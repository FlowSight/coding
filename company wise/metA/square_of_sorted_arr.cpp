//sev0
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        
        int n = nums.size(), idx = n-1, l = 0, r = n-1, tmp = 0;
        vector<int> ans(n,0);
        while(l<=r){
            if(abs(nums[l]) > abs(nums[r])) {
                ans[idx--] = nums[l] * nums[l];
                l++;
            } else {
                ans[idx--] = nums[r] * nums[r];
                r--;
            }
        }
        return ans;
    }
};

// -4,-1,0,3,100
// l       r
// 2,9,9,49,121
// lr  