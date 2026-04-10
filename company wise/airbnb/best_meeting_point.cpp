// LC : 296

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    vvi dirs = {{-1,0},{0,-1},{1,0},{0,1}};
    int minTotalDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), idx = 0, dist = 0, ans= 0;
        vi xarr, yarr;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(grid[i][j]) {
                    xarr.push_back(i);
                    yarr.push_back(j);
                }
            }
        }
        sort(xarr.begin(),xarr.end());
        sort(yarr.begin(),yarr.end());
        int l = 0, r= xarr.size()-1;
        while(l<r){
            ans += (xarr[r]-xarr[l]) + (yarr[r]-yarr[l]);
            r--;
            l++;
        }
        return ans;
    }
};


// 1  3 5 7 9
// (x-1) + (9-x) + (x-3)+(7-x) + (x-5)
// (9-1) + (7-3)