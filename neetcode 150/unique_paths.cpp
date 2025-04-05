// 17/2/25
// 5 mins
// 1 logical mistake..didnt dry run 
// sev1

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,0));
        dp[0][0] = 1;
        for(auto i=0;i<m;i++)dp[i][0] = 1;
        for(auto i=0;i<n;i++)dp[0][i] = 1;
        for(auto i=1;i<m;i++){
            for(auto j=1;j<n;j++){
                dp[i][j] = (i ? dp[i-1][j] : 0) + (j? dp[i][j-1] : 0);
            }
        }
        return dp[m-1][n-1];
    }
};
