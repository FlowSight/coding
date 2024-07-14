class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{-1,0},{0,-1},{0,1},{1,0}};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vvi pac = vvi(m,vi(n,0)), atl = vvi(m,vi(n,0)), ans = {};
        for(auto i=0;i<m;i++){
            pac[i][0] = 1;
            atl[i][n-1] = 1;
        }
        for(auto i=0;i<n;i++){
            pac[0][i] = 1;
            atl[m-1][i] = 1;
        }
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                 dfs(grid,pac,i,j);
                 dfs(grid,atl,i,j);
            }
        }
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if((pac[i][j] == 1) && (atl[i][j] == 1))ans.push_back({i,j});
            }
        }
        return ans;
    }
    int dfs(vvi& grid, vvi& visited, int r, int c){
        if(visited[r][c])return visited[r][c];
        visited[r][c] = -1;
        for(auto d : dirs){
            auto xx = d[0]+r, yy = d[1] + c;
            if(xx<0 || yy<0 || xx >= grid.size() || yy>=grid[0].size() || grid[r][c] < grid[xx][yy])continue;
            if(dfs(grid,visited,xx,yy) == 1){
                visited[r][c] = 1;
            }
        }
        return visited[r][c];
    }
};



/////////



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{0,1},{1,0},{-1,0},{0,-1}};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vvi pac = vvi(m,vi(n,0)), atl = pac, ans = {};
        queue<vi> q1, q2;
        for(auto i=0;i<n;i++){
            q1.push({0,i});
            q2.push({m-1,i});
        }
        for(auto i=0;i<m;i++){
            q1.push({i,0});
            q2.push({i,n-1});
        }
        while(!q1.empty()){
            auto tp = q1.front();
            q1.pop();
            pac[tp[0]][tp[1]] = 1;
            for(auto d : dirs){
                auto xx = d[0] + tp[0] , yy = d[1] + tp[1];
                if(xx <0 || xx >=m || yy<0 || yy>=n || grid[tp[0]][tp[1]] > grid[xx][yy] || pac[xx][yy])continue;
                q1.push({xx,yy});
            }
        }
        while(!q2.empty()){
            auto tp = q2.front();
            q2.pop();
            atl[tp[0]][tp[1]] = 1;
            for(auto d : dirs){
                auto xx = d[0] + tp[0] , yy = d[1] + tp[1];
                if(xx <0 || xx >=m || yy<0 || yy>=n || grid[tp[0]][tp[1]] > grid[xx][yy] || atl[xx][yy])continue;
                q2.push({xx,yy});
            }
        }
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(pac[i][j] && atl[i][j])ans.push_back({i,j});
            }
        }
        return ans;
    }
};