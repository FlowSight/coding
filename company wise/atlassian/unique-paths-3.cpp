class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs =  {{0,1},{1,0},{0,-1},{-1,0}};
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), sX = 0, sY = 0, empty = 0, ans = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 1) {
                    sX = i, sY = j;
                } else if(grid[i][j] == 0) empty++;
            }
        }
        dfs(grid,m,n,sX,sY,empty,ans);
        return ans;
    }

    void dfs(vvi& grid, int m, int n,int r, int c, int& empty, int& ans){
        if(grid[r][c] == 2){
            if(empty == 0) ans++;
            return;
        }
        
        for(auto d : dirs) {
            auto xx = d[0]+r, yy = d[1] + c;
            if((xx<0) || (xx>=m) || (yy<0) || (yy>=n) || (grid[xx][yy] < 0) || (grid[xx][yy] == 1)) continue;
            // coming here for 0 or 2
            auto tmp = grid[xx][yy];
            if(tmp == 0) {
                empty--;
                grid[xx][yy] = -2;
            }
            dfs(grid,m,n,xx,yy,empty,ans);
            if(tmp == 0) {
                empty++;
                grid[xx][yy] = tmp;
            }
        }
    }
};