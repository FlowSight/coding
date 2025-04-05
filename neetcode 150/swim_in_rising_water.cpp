// 23 mar 2025..
// 17 mins..didnt do a optimization..so got tle at first..
// sev2

class Solution {
    public:
        vector<vector<int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
        int swimInWater(vector<vector<int>>& grid) {
            int n = grid.size();
            priority_queue<vector<int>> pq; //{cost,i,j}
            vector<vector<int>> visited;
    
            pq.push({-grid[0][0],0,0});
            while(!pq.empty()){
                auto tp = pq.top();
                pq.pop();
    
                auto time = -tp[0], x = tp[1], y = tp[2];
                if((x==n-1) && (y==n-1)) return time;
    
                if(grid[x][y] == -1)continue;
                grid[x][y] = -1;
                
                for(auto d: dirs){
                    auto xx = d[0]+x, yy = d[1] + y;
                    if((xx<0) || (yy<0) || (xx>=n) || (yy>=n) || (grid[xx][yy] == -1)) continue;
                    auto timeToSwim = max(time,grid[xx][yy]);
                    pq.push({-timeToSwim,xx,yy});
                }
            }
            return -1;
        }
    };