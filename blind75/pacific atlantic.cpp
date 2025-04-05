// 18 mar 2025..
// i messed up again..stupid visited logic error in code..
// sev0

//11 nov 2024..below issues
// queue t push e korini..
// very stupid logical mistake in code.
// compiler error


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{1,0},{0,1},{0,-1},{-1,0}};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        queue<pair<int,int>> q;
        vvi visited(m,vi(n,0)), ans;
        for(auto i=0;i<n;i++){
            visited[0][i] = 1;
            q.push({0,i});
        }
        for(auto i=0;i<m;i++){
            visited[i][0] = 1;
            q.push({i,0});
        }

        while(!q.empty()) {
            auto tp = q.front();
            auto x = tp.first, y = tp.second;
            q.pop();

            for(auto d: dirs){
                auto xx = d[0]+x, yy = d[1]+y;
                if(xx<0 || yy<0 || xx>=m || yy>=n || visited[xx][yy] || heights[xx][yy] < heights[x][y]) continue;
                q.push({xx,yy});
                visited[xx][yy] = 1;
            }
        }

        for(auto i=0;i<n;i++){
            visited[m-1][i] = (visited[m-1][i] == 1 ? 3 : 2);
            q.push({m-1,i});
            if(visited[m-1][i] == 3)ans.push_back({m-1,i});
        }
        for(auto i=0;i<m;i++){
            visited[i][n-1] = (visited[i][n-1] == 1 ? 3 : 2);
            q.push({i,n-1});
            if(visited[i][n-1] == 3)ans.push_back({i,n-1});
        }

        while(!q.empty()) {
            auto tp = q.front();
            auto x = tp.first, y = tp.second;
            q.pop();

            for(auto d: dirs){
                auto xx = d[0]+x, yy = d[1]+y;
                if(xx<0 || yy<0 || xx>=m || yy>=n || (visited[xx][yy] == 2) || (visited[xx][yy] ==3 ) || heights[xx][yy] < heights[x][y]) continue;
                visited[xx][yy] = (visited[xx][yy] == 1 ? 3 : 2);
                q.push({xx,yy});
                if(visited[xx][yy] == 3)ans.push_back({xx,yy});
            }
        }
        return ans;

    }
};