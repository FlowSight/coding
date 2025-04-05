// 20 feb 25
// n^2 in 13 mins..clean..
// 1 complier mistake..didnt know |= of bool array element doesnt work..
// fucked up when made it 2*n space..fucked up in 0/1 iteration handling in base case..

// sev3
class Solution {
public:
    typedef vector<bool> vi;
    typedef vector<vi> vvi;
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size(), len = s3.size();
        if(len != m + n) return false;
        vvi dp(2,vi(n+1,0));

        for(auto i=0;i<=m;i++) {
            for(auto j=0;j<=n;j++){
                int idx = i+j-1;
                if(idx <0){
                    dp[0][j] = dp[1][j] = 1;
                    continue;
                }
                dp[1][j] = 0;
                if(i && (s3[idx] == s1[i-1])) {
                    dp[1][j] = dp[1][j] | dp[0][j];
                }
                if(j && (s3[idx] == s2[j-1])) {
                    dp[1][j] = dp[1][j] | dp[1][j-1];
                }
                dp[0][j] = dp[1][j];
            }
        }
        return dp[0][n];
    }
};