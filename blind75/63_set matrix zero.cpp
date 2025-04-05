// 19/2/25..
// 13 mins..
// no issue..


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), firstColZero = 0, firstRowZero = 0;
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(matrix[i][j] == 0){
                    if(i==0)firstRowZero = 1;
                    if(j==0)firstColZero = 1;
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for(auto j=1;j<n;j++){
            if(matrix[0][j] == 0){
                for(auto i=0;i<m;i++)matrix[i][j] = 0;
            }
        }
        for(auto i=1;i<m;i++){
            if(matrix[i][0] == 0){
                for(auto j=0;j<n;j++)matrix[i][j] = 0;
            }
        }
        if(firstRowZero){
            for(auto i=0;i<n;i++)matrix[0][i] = 0;
        }
        if(firstColZero){
            for(auto i=0;i<m;i++)matrix[i][0] = 0;
        }
    }
};