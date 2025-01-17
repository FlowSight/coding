

////////============================
// 25 oct 24

class Solution {
public:
    typedef vector<bool> vi;
    typedef vector<vi> vvi;
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if(m+n != s3.size())return false;
        vvi dp(m+1,vi(n+1,0));
        dp[0][0] = true;
        for(auto i=0;i<=m;i++){
            for(auto j=0;j<=n;j++) {
                if(!i && !j)continue;
                dp[i][j] = (i?((s3[i+j-1] == s1[i-1]) && dp[i-1][j]):0) || (j?((s3[i+j-1] == s2[j-1]) && dp[i][j-1]):0);
            }
        }
        return dp[m][n];
    }
};

// doesnt match sum length check
// 0,1 and 1,0 state check
// score very bad...base cases missed...

// below 1d optimization took me 13-15 mins..with many hit and error..didnt dry run
class Solution {
public:
    typedef vector<bool> vi;
    typedef vector<vi> vvi;
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if(m+n != s3.size())return false;
        if(s3.size() == 0) return true;
        vvi dp(2,vi(n+1,0));
        dp[0][0] = true;
        for(auto j=1;j<=n;j++)dp[0][j] = (s3[j-1]==s2[j-1]) && (dp[0][j-1]);
        for(auto i=1;i<=m;i++){
            for(auto j=0;j<=n;j++) {
                dp[1][j] = ((s3[i+j-1] == s1[i-1]) && dp[0][j]) || (j?((s3[i+j-1] == s2[j-1]) && dp[1][j-1]):0);
            }
            dp[0]=dp[1];
        }
        return dp[0][n];
    }
};

// below was trivial....
class Solution {
public:
    typedef vector<bool> vi;
    typedef vector<vi> vvi;
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if(m+n != s3.size())return false;
        if(s3.size() == 0) return true;
        vi dp(n+1,0);
        dp[0] = true;
        for(auto j=1;j<=n;j++)dp[j] = (s3[j-1]==s2[j-1]) && (dp[j-1]);
        for(auto i=1;i<=m;i++){
            for(auto j=0;j<=n;j++) {
                dp[j] = ((s3[i+j-1] == s1[i-1]) && dp[j]) || (j?((s3[i+j-1] == s2[j-1]) && dp[j-1]):0);
            }
        }
        return dp[n];
    }
};
