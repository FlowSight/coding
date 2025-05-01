// 27 apr 2025
// initiating dp state : became overconfident and thought not doing the exact way 
// has no implications
// sev0

class Solution {
    public:
        bool isValidPalindrome(string s, int k) {
            int n = s.size();
            return n-maxPalinSubstr(s) <= k;
        }
    
        int maxPalinSubstr(string& s){
            int n = s.size();
            vector<vector<int>> dp(n,vector<int>(n,0));
            for(auto i=0;i<n;i++)dp[i][i] = 1;
    
            for(auto len=2;len<=n;len++){
                for(auto i=0,j=i+len-1; j<n; i++,j++){
                    dp[i][j] = max({dp[i][j], dp[i+1][j], dp[i][j-1]});
                    if(s[i] == s[j]) {
                        dp[i][j] = max(dp[i][j], dp[i+1][j-1]+2);
                    }
                }
            }
            return dp[0][n-1];
        }
    };
    
    
    // acba
    // i=0
    // j=1
    // dp[0][1] = 1
    // dp[1][2] = 1
    // dp[2][3] = 1
    // dp[0][2] = 1
    // dp[1][3] = 1
    // dp[0][3] = max(dp[0][2],dp[1][3],dp[1][2]+2) = 3