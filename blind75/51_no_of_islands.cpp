// 22 dec 2024...took 20 mins to get tha fact that I should not assign grid[i][j] = '-1'
// Verdci: FAIL 

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans =  0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j] == '1') {
                    ans++;
                    dfs(grid,i,j,m,n);
                }
            }
        }
        return ans;
    }

    void dfs(vector<vector<char>>& grid, int r, int c, int m, int n) {
        if(grid[r][c] != '1') return;
        grid[r][c] = '$';
        for(auto& d : dirs) {
            auto xx = d[0] + r, yy = d[1] + c;
            if((xx <0) || (yy < 0) || (xx >= m) || (yy >=n) || (grid[xx][yy] != '1')) continue;
            dfs(grid,xx,yy,m,n);
        }
    }


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