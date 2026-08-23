/// Severity: Sev0
// Date: 22Aug26
// LC: 1510
// Where I failed: i did text book grundy, but i forgot to realize that if mex(grundy(n))  = dp[n] = 0, then loss
//  i dont actuall need to get the mex for the whole set
// Pattern: game/grundy
// Notes: additional_notes



class Solution {
public:
    bool winnerSquareGame(int n) {
        if(n<=2) return n==1?true:false;
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for(auto i=3;i<=n;i++){
            for(auto j=1;j*j<=i;j++){
                if(!dp[i-j*j]) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};

// grundy(n) = mex{grund(m)} for all m reachable from n
// dp[0] = 0, dp[1] = mex(grundy(0)) = 1
// dp[2] = mex(grundy(1)) = mex(1) = 0 