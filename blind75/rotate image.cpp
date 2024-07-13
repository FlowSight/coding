//all rotates:
// rotate clockwise 90:
// reverse row wise + transpose
// or
// transpose + reverse row wise

// rotate anti-clockwise 90:
// reverse column wise + transpose

//transpose code :
for(int i=0;i<n;i++)
{
    for(int j=i;j<n;j++) // j from i or i+1
    {
        swap(matrix[i][j],matrix[j][i]);
    }
}

//another way: encode values:
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(auto i=0;i<n;i++){
            for(auto j=0;j<n;j++){
                matrix[i][j] += 1000;
                matrix[i][j] *= 2001;
            }
        }
        for(auto i=0;i<n;i++){
            for(auto j=0;j<n;j++){
                int nextX = j,nextY = n-1-i;
                matrix[nextX][nextY] += matrix[i][j]/2001;
            }
        }
        for(auto i=0;i<n;i++){
            for(auto j=0;j<n;j++){
                matrix[i][j] %= 2001;
                matrix[i][j] -= 1000;
            }
        }
    }
};

