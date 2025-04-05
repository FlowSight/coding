// 6 feb 2025..
// 15 min..
// didnt dry run..fucked up in '-1' calc
// also missed a corner case..
// verdict : FAIL
// severity : sev2

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    int orangesRotting(vector<vector<int>>& grid) {
        deque<vi> q;
        int m = grid.size(), n = grid[0].size(), fresh = 0, time = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == 2)q.push_back({i,j});
                else if(grid[i][j] == 1)fresh++;
            }
        }
        while(!q.empty()){
            time++;
            int sz = q.size(); // 2
            while(sz--){
                auto cur = q.front();
                q.pop_front();
                auto x = cur[0], y = cur[1];
                for(auto d: dirs){
                    auto xx = x + d[0] , yy = y + d[1];
                    if(xx<0 || yy<0 || xx>=m || yy>=n || (grid[xx][yy] != 1))continue;
                    fresh--;
                    grid[xx][yy] = 2;
                    q.push_back({xx,yy});
                }
            }
        }
        return fresh ? -1 : max(0,time-1);
    }
};