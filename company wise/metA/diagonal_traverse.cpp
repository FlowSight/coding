// 22 apr 2025..
// 13 min..clean

class Solution {
    public:
        vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
            vector<int> ans;
            int m = mat.size(), n = mat[0].size(), left = 0, right = m+n-2, rev = 1;
            for(auto i=left;i<=right;i++){
                if(rev) {
                    for(auto c = 0;c<=i;c++){
                        auto r = i-c;
                        if((c>=n) || (r>=m)) continue;
                        ans.push_back(mat[r][c]);
                    }
                } else {
                    for(auto r = 0;r<=i;r++){
                        auto c = i-r;
                        if((r>=m) || (c>=n)) continue;
                        ans.push_back(mat[r][c]);
                    }
                }
                rev = rev ^ 1;
            }
            return ans;
        }
    };