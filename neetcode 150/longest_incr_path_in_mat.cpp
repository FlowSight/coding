// 20 may 2025
// missed a <= case and 1 compiler error 

// 6 apr 2025
// got it..22 min..but fumbled midway..also missed corner case..
// did digress in midway thinking its dijkstra
// sev1

// 25 feb 25
// didnt crack it..didnt remember..in simple wordss...failed..
// sev0

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans = 0;
        vvi dp(m,vi(n,0));
        for(auto i=0;i<m;i++){
            for ( auto j=0; j<n; j++){
                ans = max(ans,dfs(matrix,i,j,dp,m,n));
            }
        }
        return ans;
    }

    int dfs(vvi& mat, int r, int c, vvi& dp, int m, int n) {
        if(dp[r][c]) return dp[r][c];
        int ans = 1;
        for(auto d: dirs){
            auto xx = d[0] + r, yy = d[1]+c;
            if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (mat[xx][yy] <= mat[r][c])) continue;
            ans = max(ans,1+dfs(mat,xx,yy,dp,m,n));
        }
        return dp[r][c] = ans;
    }
};