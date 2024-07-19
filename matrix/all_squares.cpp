//LC 1277

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(matrix[i][j]) {
                    matrix[i][j] = min({(i ? matrix[i-1][j] : 0),
                        (j ? matrix[i][j-1] : 0), 
                        (i>=1 && j>=1 ?matrix[i-1][j-1] : 0)}) + 1;
                }
                ans += matrix[i][j];
            }
        }
        return ans;
    }
};

// TRICK : alll squares : matrix[i][j]  max len of squares having bottom right as i,j