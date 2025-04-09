// 9 apr
// 5min 
// clean

class Solution {
    public:
        int ans = 0;
        vector<int> row,col,topLeft, topRight;
        int totalNQueens(int n) {
            row = col = vector<int>(n,0);
            topLeft = topRight = vector<int>(2*n,0);
            helper(0,n);
            return ans;
        }
    
        void helper(int r, int& n){
            if(r == n){
                ans++;
                return;
            }
            for(auto c = 0;c<n;c++){
                if(!isValid(r,c,n)) continue;
                row[r]++;
                col[c]++;
                topLeft[r-c+n]++;
                topRight[r+c]++;
                helper(r+1,n);
                row[r]--;
                col[c]--;
                topLeft[r-c+n]--;
                topRight[r+c]--;
            }
        }
    
        bool isValid(int r, int c, int n){
            return !row[r] && !col[c] && !topLeft[r-c+n] && !topRight[r+c];
        }
    };