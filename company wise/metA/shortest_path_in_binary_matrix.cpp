// 15 jan 2025..
// 10 mins..
// logic mistake..didnt revise the code..
// verdict : FAIL

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<vector<int>> q;
        if(grid[0][0]) return -1;
        q.push({0,0,1});
        grid[0][0] = 1;

        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto cur = q.front();
                q.pop();
                if((cur[0]==n-1) && (cur[1]==n-1)) return cur[2];

                for(auto d: dirs){
                    auto x = d[0]+cur[0], y = d[1]+cur[1];
                    if(x<0 || y<0 || x>=n || y>=n || grid[x][y]) continue;
                    q.push({x,y,cur[2]+1});
                    grid[x][y] = -1;
                }
            }
        }
        return -1;
    }
};

// TODO : A* search