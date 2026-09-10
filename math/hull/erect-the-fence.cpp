/// Severity: Sev0
// Date: 28Aug26
// LC: 587
// Where I failed: algo
// Pattern: andrews monotonic hull
// Notes: additional_notes

class Solution {
public:
    typedef pair<int,int> pll;
    typedef vector<int> vi;
    typedef vector<vi> vvi;


    int crossproduct(vi& p, vi& x, vi& y){
        return (x[0]-p[0])*(y[1]-p[1]) - (x[1]-p[1])*(y[0]-p[0]);
    }
    
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(),trees.end());
        int n = trees.size(),  k = 0, lower = 0, colin = 1;
        if(n<=3) return trees;
        vvi hull(2*n,{-1,-1});

        for(auto i=0;i<n;i++){
            if((i>=2) && (crossproduct(trees[i-2],trees[i-1],trees[i]) != 0)) colin = 0;
            while((k>=2) && (crossproduct(hull[k-2],hull[k-1],trees[i]) <0)){
                k--;
            }
            hull[k++] = trees[i];
        }
        if(colin) return trees;
        lower = k+1;
        for(auto i=n-2;i>=0;i--){
            while((k>=lower) && (crossproduct(hull[k-2],hull[k-1],trees[i]) <0)) {
                k--;
            }
            hull[k++] = trees[i];
        }
        hull.resize(k-1);
        return hull;
    }
};

