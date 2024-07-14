class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<char> vc;
    typedef vector<vc> vvc;
    vvi dirs = {{0,1},{1,0},{-1,0},{0,-1}};
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0, m = grid.size(), n = grid[0].size();
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == '1'){
                    ans++;
                    dfs(grid,i,j,m,n);
                }
            }
        }
        return ans;
    }

    void dfs(vvc& grid, int& r, int& c, int& m , int& n){
        if(grid[r][c] != '1' || r>=m || c>=n )return;
        grid[r][c] = '2';
        for(auto d: dirs){
            auto xx = d[0] + r, yy = d[1] + c;
            if(xx>=0 && yy>=0 && xx<m && yy<n && (grid[xx][yy] == '1')) dfs(grid,xx,yy,m,n);
        }
        return;
    }
};