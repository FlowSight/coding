//sev0...sev0..sev0...sev0..sev0..sev0.
// absolute out of the world
// 8 nov 25

// t(n,i,p) = t(i,n-i, p, n-p)
// t(n-1,n-1,n-1,n-1) = [(0,0) to (n-1,n-1)] + [(n-1,n-1) to (0,0)] + grid[n-1][n-1] 
// or 
// [(0,0) to (n-1,n-2)] + [(n-2,n-2) to (0,0)] + grid[n-1][n-1]+grid[n-2][n-1]
// T(i,j,p,q )== max([(0,0) to (i-1,j)] + [(p-1,q) to (0,0)] , [(0,0) to (i-1,j)] + [(p,q-1) to (0,0)], .....)
//     + grid[i][j]+grid[p][q]
//     ==((i,j )has to be outsize rectangle (0,0,p,q)) && ((p,q) has to be outsize rectangle (0,0,i,j))
//     == ((i==p) && (j==q)) || ((i<p) && (j>q)) || ((i>p) && (j<q))
//     === i goes up => j goes down (same for p,q)
//     === (i+j == n) && (p+q==n) && n in (0,2N-2)
//     === (j==n-i) && (q = n-p)
//     === T(i,n-i,p,n-q) == T(n,i,p)
// T(n,i,p) = grid[i][n-i] +. grid[p][n-p] + max(T(n-1,i-1,p-1),T(n-1,i-1,p),...)
// solve for T(n-1,n-1,n-1,n-1) = T(2N-2,n-1,n-1)
// for(auto n=1;n<=2N-1;n++){
//     for(auto i=N-1;i>=0;i--){
//         for(auto j=n-i;j>=0;j--){
//     }
// }



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), N = 2*n-2;
        vvvi dp(N+1,vvi(n,vi(n,-1)));
        dp[0][0][0] = grid[0][0];
        for(auto sz = 1;sz<=N;sz++){
            for(auto i=0;i<n;i++){
                for(auto p=0;p<n;p++) {
                    int j = sz-i, q = sz - p;
                    if((j<0) || (q<0) || (j>=n) || (q>=n) || (grid[i][j] == -1) || (grid[p][q] == -1)) {
                        dp[sz][i][p] = -1;
                        continue;
                    }
                    dp[sz][i][p] = max(dp[sz][i][p],dp[sz-1][i][p]); 
                    if(i) dp[sz][i][p] = max(dp[sz][i][p],dp[sz-1][i-1][p]);
                    if(p) dp[sz][i][p] = max(dp[sz][i][p],dp[sz-1][i][p-1]);
                    if(i && p) dp[sz][i][p] = max(dp[sz][i][p],dp[sz-1][i-1][p-1]);
                    if(dp[sz][i][p] >=0) dp[sz][i][p] += grid[i][j] + (i!=p ? grid[p][q]:0);
                    // if(grid[i][j] != -1) dp[sz][i][p] += grid[i][j];
                    // if(grid[p][q] != -1) dp[sz][i][p] += (i==p ? 0 : grid[p][q]);
                }
            }
        }
        return max(0,dp[N][n-1][n-1]);
    }
};

