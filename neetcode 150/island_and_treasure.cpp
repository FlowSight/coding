// 16/2/25
// 15 mins..
// 2 compiler mistake..
// sev1
// verdict : FAIL
// https://neetcode.io/problems/islands-and-treasure

class Solution {
public:
    int INF = 2147483647;
    vector<vector<int>> dirs = {{1,0},{0,1},{0,-1},{-1,0}};
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 0){
                    //grid[i][j] = -1;
                    dfs(grid,i,j,0,m,n);
                    grid[i][j] = 0;
                    
                }
            }
        }
    }
    void dfs(vector<vector<int>>& grid, int r,int c, int dist, int m, int n){
        //if((grid[r][c] <= 0) || (grid[r][c] <= dist)) return;
        grid[r][c] = dist;
        for(auto d : dirs){
            auto xx = d[0]+r, yy = d[1]+c;
            if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (grid[xx][yy]<=0) 
                || (grid[xx][yy]<=dist+1))continue;
            dfs(grid,xx,yy,dist+1,m,n); 
        }
    }

};
