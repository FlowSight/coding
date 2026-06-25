/// Severity: Sev0
// Date: 14Jun26
// LC: 3743
// Where I failed: algo..2 algos: find max + buy sell stock..both failed.
// Pattern: dp
// Notes: additional_notes



class Solution {
public:
    typedef vector<long long> vl;
    typedef vector<vl> vvl;
    typedef vector<vvl> vvvl;
    long long maximumScore(vector<int>& nums, int k) {
        int idx = 0, n = nums.size();
        for(auto i=1;i<n;i++){
            if(nums[i] > nums[idx]) idx = i;
        }
        return max( helper(nums,idx,idx+n-1,k), helper(nums,idx+1,idx+n,k));
    }
    // the reaon for doing K=k-1 to 0 is dp[K][1] is dependent on dp[K-1]..so..if we 
    // do increasing loop, dp[k-1] will be for current i
    // pattern, when collapsing space: if dp[i][j] = func(dp[i+1][j-1]) then reverse j's direction in loop
    // if dp[i][j] =  func(dp[i+1][j+1])..then fine
    long long helper(vector<int>& arr, int l, int r, int& k){
        int n = arr.size();
        long long minval = -1e9;
        vvl dp(k+1,{minval,minval,minval});
        
        //from last, any no of partitions, with noop state
        for(auto i=0;i<=k;i++)dp[i][0] = 0;

        for(auto i=n,j=r;i>=1;i--,j--){
            for(auto K=k;K>=0;K--){
                // from i, with K partitions, 
                // max(skip,buy,short sell)
                int price = arr[j%n];
                dp[K][0] = max(dp[K][0], max(-price + dp[K][1], price+dp[K][2]));
                if(K){
                    // already bought, now sell
                    dp[K][1] = max(dp[K][1],price + dp[K-1][0]); 
                    //now buy
                    dp[K][2] = max(dp[K][2],-price + dp[K-1][0]); 
                }

            }
        }
        return dp[k][0];
    }
};



// You are given a cyclic array nums and an integer k.

// Partition nums into at most k subarrays. As nums is cyclic, these subarrays may wrap around from the end of the array back to the beginning.

// The range of a subarray is the difference between its maximum and minimum values. The score of a partition is the sum of subarray ranges.

// Return the maximum possible score among all cyclic partitions.
