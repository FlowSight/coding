// 20 feb 25..
// n^2 is 6 mins..no mistake
// O(n) space : made a logical mistake..10 mins..
// sev1

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();

        vector<vector<int>> dp(2,vector<int>(n+1,1001));
        for(auto i=0;i<=n;i++) dp[0][i] = i;
        for(auto i=1;i<=m;i++){
            for(auto j=0;j<=n;j++){
                if(j==0){
                    dp[1][j] = i;
                    continue;
                }
                dp[1][j] = min({dp[0][j-1]+1 /* replace */, dp[0][j]+1/*delete*/,dp[1][j-1]+1});
                if(word1[i-1] == word2[j-1]) {
                    dp[1][j] = min(dp[1][j],dp[0][j-1]);
                }
            }
            dp[0] = dp[1];
        }
        return dp[0][n];
    }
};