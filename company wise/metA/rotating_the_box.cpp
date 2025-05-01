// 22 apr 2025
// easy qs..i was in a hurry, messed up with index calc.
// sev3

class Solution {
    public:
        vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
            int m = boxGrid.size(), n = boxGrid[0].size();
            vector<vector<char>> ans(n,vector<char>(m,'.'));
            for(auto i=m-1;i>=0;i--){
                for(auto j=n-1,floor = n;j>=0;j--){
                    if(boxGrid[i][j] == '*') {
                        floor = j;
                        ans[j][m-1-i] = '*';
                    } else if(boxGrid[i][j] == '.') {
                        ans[j][m-1-i] = '.';
                    } else {
                        ans[--floor][m-1-i] = '#';
                    }
                }
            }
            return ans;
        }
    };
    
    // *.
    // *#
    // ##
    // ..
    