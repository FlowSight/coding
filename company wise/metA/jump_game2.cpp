    int jump(vector<int>& nums) {
        int idx = 0, maxJump = 0, n = nums.size(), ans = 0, tmpJump = nums[0];
        for(auto i=0;i<n && (maxJump <n-1);i++){
            tmpJump = max(tmpJump, i+nums[i]);
            if(maxJump == i) {
                ans++;
                maxJump = tmpJump;
            }
        }
        return ans;
    }