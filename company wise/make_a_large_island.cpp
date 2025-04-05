// 1 apr 2025.
// missed a corner case..
// sev1
// also took long time to implement..
// 20 mins

class Solution {
    public:
        unordered_map<int,int> mm;
        vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
        int largestIsland(vector<vector<int>>& grid) {
            int cnt = 2, n = grid.size(), ans = 0;
            mm.clear();
    
            for(auto i=0;i<n;i++){
                 for(auto j=0;j<n;j++){
                    if(grid[i][j] == 0)continue;
                    if(grid[i][j] > 1) continue;
                    dfs(grid,i,j,cnt,n);
                    ans = max(ans,mm[cnt++]);
                 }
            }
    
            unordered_set<int> neighbours;
            for(auto i=0;i<n;i++){
                 for(auto j=0,cur = 1;j<n;j++,cur = 1){
                    if(grid[i][j])continue;
                    
                    for(auto d : dirs){
                        auto xx = d[0] + i, yy = d[1] + j;
                        if((xx<0 )|| (yy<0) || (xx>=n) || (yy>=n) || (grid[xx][yy] == 0)) continue;
                        neighbours.insert(grid[xx][yy]);
                    }
                    for(auto it : neighbours){
                        cur += mm[it];
                    }
                    ans = max(ans, cur);
                    neighbours.clear();
                 }
            }
            return ans;
        }
    
        void dfs(vector<vector<int>>& grid, int& r, int& c, int& cnt, int& n){
            if(grid[r][c] == 0) return;
            if(grid[r][c] > 1) return;
            grid[r][c] = cnt;
            mm[cnt]++;
            for(auto d : dirs){
                auto xx = d[0] + r, yy = d[1] + c;
                if((xx<0 )|| (yy<0) || (xx>=n) || (yy>=n) || (grid[xx][yy] == 0) || (grid[xx][yy] > 1)) continue;
                dfs(grid,xx,yy,cnt,n);
            }
        }
    };
    