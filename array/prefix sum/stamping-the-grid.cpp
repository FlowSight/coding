/// Severity: Sev0
// Date: 04Nov26
// LC: 2132
// Where I failed: didnt even get the idea.didnt get that covering all hXw matrices
// are needed and marking at bottom left
// Pattern: prefix sum in 2d
// Notes: additional_notes


class Solution {
public:

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi prefsum(vvi& grid){
        int m = grid.size(), n = grid[0].size();
        vvi pre(m+1,vi(n+1,0));
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                pre[i+1][j+1] = pre[i+1][j] + pre[i][j+1] + grid[i][j] - pre[i][j];
            }
        }
        return pre;
    }

    int getsum2d(vvi& grid, int r1,int c1, int r2, int c2){
        return grid[r2][c2] - grid[r2][c1-1] - grid[r1-1][c2] + grid[r1-1][c1-1]; 
    }
    bool isStamped(vvi& grid,  int r1, int c1, int r2, int c2){
        return getsum2d(grid,r1,c1,r2,c2); // if any 1 is in that subgrid, its stamped
    }

    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
         int m = grid.size(), n = grid[0].size();
         auto pre = prefsum(grid);
         vvi stamp(m,vi(n,0));
         for(auto i=stampHeight;i<=m;i++){
            for(auto j=stampWidth;j<=n;j++) {
                stamp[i-1][j-1] = (getsum2d(pre,i-stampHeight+1,j-stampWidth+1,i,j) == 0);
                //if(stamp[i-1][j-1]) cout<<i-1<<" "<<j-1<<endl;
            }
         }
         auto pre2 = prefsum(stamp);
         for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                if((grid[i-1][j-1] == 0) && (!isStamped(pre2,i,j,min(i+stampHeight-1,m),min(j+stampWidth-1,n)))) return false;
            }
        }
        return true;
    }
};

// calc pref sum of grid
// for each hXw subgrid, stamp it at bot left if applicable , in another empty subgrid
// for each 0 cell, check if its stamped, else return false




// 1 2 3 4 
// 5 *6 7 8
// 9 2 4 5 
// 2 4 5 5