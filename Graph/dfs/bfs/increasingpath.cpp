// LC 329

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dirs = {{0,1},{1,0},{0,-1},{-1,0}};

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(),ans = 0;
        vvi visited = vvi(m,vi(n,0));
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                ans = max(ans,dfs(matrix,i,j,visited, m, n));
            }
        }
        return ans;
    }

    int dfs(vvi& matrix, int r, int c, vvi& visited, int m , int n){
        if(visited[r][c] != 0)return visited[r][c];
        int ans = 0;
        for(auto d : dirs){
            auto xx = d[0] + r, yy = d[1] + c;
            if(xx<0 || yy<0 || xx>=m || yy>=n || matrix[xx][yy] <= matrix[r][c])continue;
            ans = max(ans,dfs(matrix,xx,yy,visited,m,n));
        }
        return visited[r][c] = 1+ans;
    }
};


// didn't think about the fact that for increasing sequence same node cant be visited twice...so dfs would work in n^2

