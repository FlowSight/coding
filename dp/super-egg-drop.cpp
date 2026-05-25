/// Severity: Sev0..sev0..sev0..sev0..
// Date: 25May26
// LC: 887
// Where I failed: algo..differently modelled dp..
// Pattern: dp
// Notes: additional_notes



class Solution {
public:
    int superEggDrop(int k, int n) {
        int move = 0;
        vector<vector<int>> dp(2,vector<int>(k+1,0));// with i move and j eggs
        for(;dp[1][k] < n;){
            move++;
            for(auto j=1;j<=k;j++) dp[1][j] = 1+dp[0][j-1]+dp[0][j];
            dp[0] = dp[1];
        }
        return move;
    }
};