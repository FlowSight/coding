/// Severity: Sev0..sev0..sev0
// Date: 20May26
// LC: 1568
// Where I failed: dfs/bfs x each cell..i went on wrong path of algo that only border nodes
//    can be ans..whch is not true
// Pattern: bfs/dfs + group check
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), done = 0, cnt = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 1) {
                    if(!done){
                        if(islandcnt(grid,i,j) == 2) return 0;
                        done = 1;
                    }
                    cnt++;
                }
            }
        }
        if(cnt <=1) return cnt;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 1) {
                    grid[i][j] = 0;
                    for(auto d : dirs){
                        auto xx = d[0] + i , yy = d[1] + j;
                        if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (grid[xx][yy] != 1)) continue;
                        if(islandcnt(grid,xx,yy) == 2) return 1;
                        break;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }

    int islandcnt(vvi& grid, int r, int c){
        int m = grid.size(), n = grid[0].size();
        queue<vi> q;
        q.push({r,c});
        grid[r][c] = -1;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto tp = q.front();
                q.pop();
                for(auto d : dirs){
                    auto xx = d[0] + tp[0] , yy = d[1] + tp[1];
                    if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (grid[xx][yy] != 1)) continue;
                    grid[xx][yy] = -1;
                    q.push({xx,yy});
                }
            }
        }
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 1) return 2;
                if(grid[i][j] == -1) grid[i][j] = 1;
            }
        }
        return 1;
    }
};