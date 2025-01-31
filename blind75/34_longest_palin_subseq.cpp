// 26 jan 2025..
// 5 mins for n^3 approach..
// 10 mins for n^2 approach with dp..but also with 3 logical mistakes..
// cound not do manachar
// verdict : FAIL

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    string longestPalindrome(string s) {
        int ansL = 0, maxLen = 1, n = s.size();
        string ans = "";
        vvi dp(n,vi(n,0));

        for(auto i=0;i<n;i++)dp[i][i]=1;

        for(auto len=2;len<=n;len++){
            for(auto i=0,found = 0;(i+len-1)<n;i++,found = 0){
                if(s[i]!=s[i+len-1])continue;
                if((len == 2) || dp[i+1][i+len-2]){
                    found = 1;
                }
                if(found){
                    dp[i][i+len-1] = 1;
                    ansL = i;
                    maxLen = len;
                }
            }
        }
        return s.substr(ansL,maxLen);
    }
};

/// @brief /////////
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size(), ansL = 0, ansR = 0;
        vector<vector<bool>> dp(n,vector<bool>(n,0));
        for(auto i=0;i<n;i++){
            dp[i][i] = 1;
            if(i<n-1 && (s[i]==s[i+1])){
                dp[i][i+1] = 1;
                ansL = i;
                ansR = i+1;
            } 
        }
        for(auto len = 3;len<=n;len++){
            for(auto i=0;i+len-1<n;i++){
                dp[i][i+len-1] = (s[i]==s[i+len-1]) && (dp[i+1][i+len-2]);
                if(dp[i][i+len-1] && (ansR-ansL+1 < len)){
                    ansL = i;
                    ansR = i+len-1;
                }
            }
        }
        return s.substr(ansL,ansR-ansL+1);
    }
};