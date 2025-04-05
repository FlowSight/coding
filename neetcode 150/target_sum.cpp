// 17/2/25
// did rute force in 5 mins..
// iterative dp was incorrect..got the state right but messed up indexing
// didnt cme up with recursive dp 
// sev0



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int findTargetSumWays(vector<int>& nums, int target) {
        int ans = 0, idx = 0 ,cur = 0, n = nums.size();
        dp = vvi(n+1,vi(2001,0));
        dp[0][1000] = 1;
        
        for(auto i=1;i<=n;i++){
            for(auto j=0;j<=2000;j++){
                auto remPlus = j-nums[i-1], remMinus = j+nums[i-1];
                
                dp[0][j] = dp[1][j] = (remPlus>=0? dp[0][remPlus] : 0) + (remMinus< 2001 ? dp[0][remMinus] : 0);
            }
        }
        return dp[n][target+1000];
    }

};