


    int helper(vector<int>& nums, set<int>& levels) {
        unordered_map<int,int> dp;
        for(auto num : nums) {
            int cur_res = INT_MAX;
            for(auto level : levels) {
                cur_res = min(cur_res, dp[level]+abs(num-level));
                dp[level] = cur_res;
            }
        }
        return dp[*--levels.end()];
    }
    int convertArray(vector<int>& nums) {
        set<int> levels(nums.begin(),nums.end());
        vector<int> nums2 = nums;
        reverse(nums2.begin(),nums2.end());
        return min(helper(nums,levels),helper(nums2,levels));
    }

    

// You are given a 0-indexed integer array nums. In one operation, you can:

// Choose an index i in the range 0 <= i < nums.length
// Set nums[i] to nums[i] + 1 or nums[i] - 1
// Return the minimum number of operations to make nums non-decreasing or non-increasing.