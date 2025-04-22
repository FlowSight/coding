// 10 apr 2025
// i tried doing bitset + dp..fucked up as i did not have grip over it..
// resorted back to backtrack..one corner case fuckup..
// sev0

// TODO: https://leetcode.com/problems/unique-paths-iii/solutions/4872507/bitmask-dp

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        vvi dirs = {{0,1},{1,0},{-1,0},{0,-1}};
        int ans;
        int uniquePathsIII(vector<vector<int>>& grid) {
            int m = grid.size() , n =  grid[0].size(), visited = 0, startX = 0, startY = 0,
                endX = 0, endY = 0, empty = 1;
            ans = 0;
            for(auto i=0;i<m;i++){
                for(auto j=0;j<n;j++){
                    if(grid[i][j] == 1){
                        startX = i;
                        startY = j;
                    }
                    else if(grid[i][j] == 0){
                        empty++;
                    }
                }
            }
            dfs(grid,startX,startY,visited,empty,m,n);
            return ans;
        }
    
        void dfs(vvi& grid,int& r,int& c,int& visited,int& empty, int& m ,int& n){
            if(grid[r][c] == -1) return;
            if(grid[r][c] == 2) {
                if(visited == empty)ans++;
                return;
            }
            int tmp = grid[r][c];
            grid[r][c] = -1;
            visited++;
            for(auto d: dirs){
                auto xx = d[0] + r, yy = d[1]+c;
                if((xx<0) || (xx>=m) || (yy<0) || (yy>=n) || (grid[xx][yy] == -1))continue;
                dfs(grid,xx,yy,visited,empty,m,n);
            }
            visited--;
            grid[r][c] = tmp;
        }
    };
    