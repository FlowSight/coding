// 22 apr 2025..
// failed. thought of dp..butdidnt  get it properly..
// take/no take pattern..
// could not do O(1)..then realized its not EXACTLy no space its O(1)
// sev0  sev0


class Solution {
    public:
        long long mostPoints(vector<vector<int>>& arr) {
            int n = arr.size();
            vector<long long> dp(n+1,0);
            long long ans = 0;
            for(auto i=n-1;i>=0;i--){
                int right = min(n,arr[i][1]+i+1);
                dp[i] = max(dp[i+1],dp[right]+arr[i][0]);
                ans = max(ans,dp[i]);
            }
            return ans;
        }
    };