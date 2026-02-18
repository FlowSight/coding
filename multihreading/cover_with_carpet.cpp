/// Severity: Sev0
// Date: 18Feb26
// 
// Where I failed: description
// Pattern: dp
// Notes: additional_notes
//


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size();
        vvi dp(n+1,vi(numCarpets+1,n+1));
        //for(auto i=0;i<=numCarpets;i++)dp[0][i] = 0;
        for(auto i=1;i<=n;i++)dp[i][0] = (i?dp[i-1][0]:0) + (floor[i-1]=='1');
        for(auto i=1;i<=n;i++){
            for(auto j=1;j<=numCarpets;j++) {
                auto cover = dp[max(0,i-carpetLen)][j-1], nocover = (i?dp[i-1][j]:0 )+ (floor[i-1] == '1');
                dp[i][j] = min({dp[i][j],cover,nocover});
            }
        }
        return dp[n][numCarpets];
    }
};