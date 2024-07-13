class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        for(auto i=0,lim = 0;i<=min(n-1,lim);i++){
            lim = max(lim,i+nums[i]);
            if(lim >=n-1)return true;
        }
        return false;
    }
};