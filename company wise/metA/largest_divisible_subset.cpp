
// 22 apr 2025
// i decided to make graph and do dfs..it should still work..but didnt do
// could not come up with dp solution + made mistake in coding dp sol
// also there is a slight trick in dfs approach
// sev1

class Solution {
    public:
        vector<int> largestDivisibleSubset(vector<int>& nums) {
            int n = nums.size(), ans = 0;
            sort(nums.begin(), nums.end());
            vector<int>  dp(n,1), res;
    
    
            for(auto i=1;i<n;i++){
                for(auto j=i-1;j>=0;j--){
                    if(nums[i] % nums[j]) continue;
                    dp[i] = max(dp[i],dp[j]+1);
                }
                if(dp[i] > dp[ans]) ans = i;
            }
            for(auto i=ans;(i>=0) && (dp[ans]>0);i--){
                if((dp[i] != dp[ans]) || ( res.size() && (res.back() % nums[i]))) continue;
                res.push_back(nums[i]);
                dp[ans]--;
            }
    
            reverse(res.begin(),res.end());
            return res;
        }
    };