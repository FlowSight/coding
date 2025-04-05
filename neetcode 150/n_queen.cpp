// 10 feb 2025
// 10 mins..
// 1 compiler error
// verdict : fAIL
// severity : 3

class Solution {
public:
    vector<vector<string>>  ans;
    vector<int> row, col, topLBotR, topRbotL;
    vector<vector<string>> solveNQueens(int n) {
        ans = {};
        row = vector<int>(n,0);
        col = vector<int>(n,0);
        topLBotR = vector<int>(2*n,0);
        topRbotL = vector<int>(2*n,0);

        vector<string> cur(n,string(n,'.'));
        helper(n,cur,0);
        
        return ans;
    }

    void helper(int n,vector<string>& cur, int r){
        if(r>=n) {
            ans.push_back(cur);
            return;
        }
        for(auto c=0;c<n;c++){
            if(row[r] || col[c] || topLBotR[r-c+n] || topRbotL[r+c] ) continue;

            cur[r][c] = 'Q';
            row[r] = col[c] = topLBotR[r-c+n] = topRbotL[r+c] = 1;
            helper(n,cur,r+1);

            cur[r][c] = '.';
            row[r] = col[c] = topLBotR[r-c+n] = topRbotL[r+c] = 0;
        }
    }
