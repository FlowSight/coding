

#include<bits/stdc++.h>

using namespace std;;

typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<vc> vvc;

int boardscore(vs grid){
    int m = grid.size(), n = grid[0].size(), rowcur = 1, colcur = 1,ans =0;
    vi colcurs(n,0);
    for(auto i=0;i<m;i++){
        for(auto j=0;j<n;j++){
            if(!j || (grid[i][j] != grid[i][j-1])) {
                rowcur = 1;
            } else {
                rowcur++;
            }
            if(!i || (grid[i][j] != grid[i-1][j])) {
                colcurs[j] = 1;
            } else {
                colcurs[j]++;
            }
            ans += rowcur + colcurs[j];
        }
    }
    return ans;
}
int main(){
    vs  grid = {
        "ABC","DEF","GHI"
    };
    cout<<boardscore(grid)<<endl;
    return 0;
}

// 0,0 rowcur = 1 colcur = 1 ans = 2 
// 0,1 rowcur = 2 colcur = 1 ans = 5
// 1,0 rowcur = 1 colcur = 1 ans = 2 