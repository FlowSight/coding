11 jan 2025..
i lost it..made error in dp state..i didnt get to the bottom of dp state thinking.was rushing through it.
Also, failed to make it O(1) space..struggled there..
verdict : FAIL // TODO

    int rob(vector<int>& nums) {
        int n = nums.size(), dp0 = 0, dp1 = nums[0], dp2 = 0;
        for(auto i=2;i<=n;i++){
            dp2 = max(dp1,dp0 + nums[i-1]);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp1;
    }