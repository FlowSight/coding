// 3 may 2025..
// 1 logical mistake..very silly

class Solution {
    public:
        unordered_map<int,vector<int>> mm;
        vector<vector<int>> dp;
        int mod = 1e9+7;
        int knightDialer(int n) {
            int ans = 0;
            dp = vector<vector<int>>(10,vector<int>(n+1,-1));
            for(auto i=0;i<=9;i++) dp[i][1] = 1;
            mm[0] = {4,6};
            mm[1] = {6,8};
            mm[2] = {7,9};
            mm[3] = {4,8};
            mm[4] = {3,9,0};
            mm[5] = {};
            mm[6] = {1,7,0};
            mm[7] = {6,2};
            mm[8] = {1,3};
            mm[9] = {4,2};
            for(auto i=0;i<=9;i++){
                ans = (ans + dfs(i,n))%mod;
            }
            return ans;
        }
    
        int dfs(int idx, int len){
            if(dp[idx][len] != -1) return dp[idx][len];
            int ans = 0;
            for(auto v : mm[idx]){
                ans = (ans + dfs(v,len-1)) %mod;
            }
            return dp[idx][len] = ans;
        }
    };
    
    
    