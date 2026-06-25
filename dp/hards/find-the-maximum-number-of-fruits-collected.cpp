
/// Severity: Sev0..sev0..sev0..sev0.sev0.sev0.sev0..sev0..sev0.sev0.sev0.sev0..sev0..sev0.sev0.sev0.
// Date: 01Jun26
// LC: 3363
// Where I failed: algo..didnt read qs carefully..player optimal path is in a zone
// Pattern: dp + path pattern design
// Notes: additional_notes



class Solution {
public:
    vector<vector<int>> dp;
    int maxCollectedFruits(vector<vector<int>>& grid) {
        int n = grid.size(), ans = 0;
        for(auto i=0;i<n;i++){
            ans += grid[i][i];
            grid[i][i] = 0;
        }
        dp = vector<vector<int>>(n,vector<int>(n,-1));
        ans += dfs2(grid,0,n-1)+ dfs3(grid,n-1,0);
        return ans;
    }
    int dfs2(vector<vector<int>>& grid, int r, int c){
        if(r<0 || (c<0) || (r>=grid.size()) || (c>=grid.size())) return 0;
        int ans = 0;
        if(dp[r][c] != -1) return dp[r][c];
        if(r==c) ans = dfs2(grid,r+1,c+1);
        else if(r==c-1) ans = max(dfs2(grid,r+1,c),dfs2(grid,r+1,c+1));
        else ans = max({dfs2(grid,r+1,c),dfs2(grid,r+1,c+1), dfs2(grid,r+1,c-1)});
        return dp[r][c] = ans+grid[r][c];
    }
    int dfs3(vector<vector<int>>& grid, int r, int c){
        if((r<0) || (c<0) || (r>=grid.size()) || (c>=grid.size())) return 0;
        int ans = 0;
        if(dp[r][c] != -1) return dp[r][c];
        if(r==c) ans = dfs3(grid,r+1,c+1);
        else if(r==c+1) ans = max(dfs3(grid,r,c+1),dfs3(grid,r+1,c+1));
        else ans = max({dfs3(grid,r-1,c+1),dfs3(grid,r,c+1), dfs3(grid,r+1,c+1)});
        return dp[r][c] = ans+grid[r][c];
    }
};



class Solution {
public:
        int maxCollectedFruits(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i < j && j < n - 1 - i) {
                    grid[i][j] = 0;
                }
                if (j < i && i < n - 1 - j) {
                    grid[i][j] = 0;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += grid[i][i];
            grid[i][i] = 0;
        }
        // this does not calculate for  cells where player2 cant go
        for (int i = 1; i < n-1; ++i) {
            for (int j = n-1; j >=0; j--) {
                if(i>j) break;
                int ma = grid[i-1][j];
                ma = max({ma,(j?grid[i-1][j-1]:0) , (j+1<n ? grid[i-1][j+1]:0)});
                grid[i][j] += ma;
            }
        }
        // this does not calculate for  cells where player1 cant go
        for (int c = 1; c < n-1; c++) {
            for (int r = n-1; r>=0; r--) {
                if(r<c) break;
                int ma = grid[r][c-1];
                ma = max({ma,(r?grid[r-1][c-1]:0) , (r+1<n ? grid[r+1][c-1]:0)});
                grid[r][c] += ma;
            }
        }
        return res + grid[n - 1][n - 2] + grid[n - 2][n - 1];;
    }
};

// 24+34+42