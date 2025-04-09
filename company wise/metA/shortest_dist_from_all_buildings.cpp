// 8 apr 2025
// I did m^2n^2..correct approach..only that the question expected a diff optimization..i.e. 
//     start from the houses
// also in my code, i did few silly compiler and logical error.
// sev0


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{0,1},{1,0},{0,-1},{-1,0}};
    vvi visited;
    int shortestDistance(vector<vector<int>>& grid) {
        
        int m = grid.size(), n = grid[0].size(), ans = m*n*m*n, house = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 1) house++;
            }
        }
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 0) {
                    ans = min(ans,tryPlace(grid,i,j,m,n, house));
                }
            }
        }
        return ans == m*n*m*n ? -1 : ans;
    }

    int tryPlace(vvi& grid, int r, int c, int& m, int& n, int house){
        queue<vector<int>> q;
        visited = grid;
        q.push({r,c});
        int cost = 0, x = 0, y = 0, ans = 0;
        while(!q.empty()) {
            cost++;
            auto sz = q.size();
            while(sz--){
                auto cur = q.front();
                q.pop();
                x = cur[0];
                y = cur[1];
                for(auto d: dirs){
                    auto xx = d[0]+x, yy = d[1]+y;
                    if((xx<0) || (yy<0) || (xx>=m) || (yy>=n) || (visited[xx][yy] == 2)) continue;
                    if(visited[xx][yy] == 1) { // if a house untravelled
                        ans += cost;
                        visited[xx][yy] = 2;
                        house--;
                        continue;
                    }
                    visited[xx][yy] = 2; // mark travelled if a empty cell
                    q.push({xx,yy});
                }
            }
        }
        return house == 0 ? ans :  m*n*m*n;
    }
};