// 19 march 2025
// failed..didnt write correct dp state to begin with..
// sev0

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        vvi dp;
        bool isMatch(string s, string p) {
            int m = s.size(), n = p.size();
            dp = vvi(m+1, vi(n+1,0));
            dp[0][0] = 1;
    
            for(auto i=1;i<n;i++){
                if((p[i] != '*') && (p[i-1] != '*')) break;
                if((p[i] == '*') && (p[i-1] != '*')) {
                    dp[0][i] = dp[0][i+1] = 1;
                }
            }
    
            for(auto i=1;i<=m;i++){
                for(auto j=1;j<=n;j++){
                    if(p[j-1] == '*'){
                        dp[i][j] = dp[i][j-2] || (((p[j-2] == '.') || (p[j-2]==s[i-1])) && dp[i-1][j]);
                        // this is done because.dp[i-1][j] means  s[0....i-2] matches upto p[j], hence only need to match i-1th char
                    } else {
                        dp[i][j] = ((p[j-1] == '.' )|| (p[j-1]==s[i-1])) && dp[i-1][j-1];
                    }
                }
            }
            return dp[m][n];
        }
    };
    
    
    