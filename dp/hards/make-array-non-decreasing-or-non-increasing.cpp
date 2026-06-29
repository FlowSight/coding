
/// Severity: Sev0
// Date: 29Jun26
// LC: 2263
// Where I failed: got confused in dp state
// Pattern: dp with prefix min
// Notes: additional_notes



class Solution {
public:
    set<int> ss;
    int helper(vector<int> arr){
        unordered_map<int,int> dp;
        for(auto it : arr){
            int cur = INT_MAX;
            for(auto it1 : ss){
                dp[it1] = cur = min(cur,dp[it1] + abs(it1-it));
            }
        }
        return dp[*prev(ss.end())];
    }
    int convertArray(vector<int>& nums) {
        for(auto it : nums)ss.insert(it);
        vector<int> arr = nums;
        reverse(arr.begin(),arr.end());
        return min(helper(arr),helper(nums));
    }
};

// dp[i][j] = till i, keeping arr[i] <=j and 0..i non-decreasing, min score is how much?
//      = min(dp[i-1][x] + abs(arr[i]-x) ) for x<=j

    

// You are given a 0-indexed integer array nums. In one operation, you can:

// Choose an index i in the range 0 <= i < nums.length
// Set nums[i] to nums[i] + 1 or nums[i] - 1
// Return the minimum number of operations to make nums non-decreasing or non-increasing.