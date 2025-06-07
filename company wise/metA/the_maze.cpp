class Solution {
public:
    vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
        if(maze[start[0]][start[1]]) return false;
        if(maze[dest[0]][dest[1]]) return false;

        int m = maze.size(), n = maze[0].size(), r = 0, c = 0;

        queue<vector<int>> q;
        q.push(start);
        maze[start[0]][start[1]] = -1;

        while(!q.empty()){
            auto sz = q.size();
            while(sz--){
                auto cur = q.front();
                r = cur[0], c = cur[1];
                if((r== dest[0]) && (c==dest[1])) return true;
                q.pop();

                for(auto& d : dirs){
                    auto xx = r, yy = c;
                    while(isValid(maze,xx+d[0],yy+d[1],m,n)) {
                        xx+=d[0], yy += d[1];
                    }
                    if(maze[xx][yy] == 0) {
                        maze[xx][yy] = -1;
                        q.push({xx,yy});
                    }

                }
            }
        }
        return false;
    }

    bool isValid(vector<vector<int>>& maze, int r, int c, int m, int n){
        if((r<0) || (c<0) || (r>=m) || (c>=n) || (maze[r][c] == 1)) return false;
        return true;
    }
};