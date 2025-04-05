// 19 mar 2025
// got that its dp and divide and rule..but didnt remember the crunch
// its last baloon to burst..not the first one
// sev0


class Solution {
    public:
        vector<vector<int>> dp;
        int maxCoins(vector<int>& nums) {
            vector<int> arr;
            arr.push_back(1);
            for(auto it : nums){
                arr.push_back(it);
            }
            arr.push_back(1);
    
            int n = nums.size();
            dp = vector<vector<int>>(n+1,vector<int>(n+1,-1));
            return helper(arr,1,n);
        }
    
        int helper(vector<int>& arr, int l, int r){
            if(l>r) return 0;
            if(dp[l][r] != -1) return dp[l][r];
            if(l == r) return dp[l][r] = arr[l]*arr[l-1]*arr[l+1];
            
            int ans = -1;
            for(auto i=l;i<=r;i++){
                ans = max(ans,helper(arr,l,i-1) + arr[l-1]*arr[i]*arr[r+1] + helper(arr,i+1,r));
            }
            return dp[l][r] = ans;
        }
    };