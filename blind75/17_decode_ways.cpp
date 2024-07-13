class Solution {
public:
    long mod = 1e11+7;
    int numDecodings(string s) {
        int n = s.size();
        vector<long> dp(n+1,0);
        dp[0] = 1;
        for(auto i=1;i<=n;i++){
            string cur = "";
            cur.push_back(s[i-1]);
            if(cur > "0")dp[i] = (dp[i] + dp[i-1])%mod;
            cur.push_back((i > 1 ? s[i-2] : '9'));
            reverse(cur.begin(),cur.end());
            if((cur >= "10") && (cur <= "26")){
                dp[i] = (dp[i] + dp[i-2])%mod;
            }
        }
        return dp.back();
    }
};

// A B C 
// A : 1
// B : 2
// Z : 26
// dp[i] = no of ways to decode upto i
//        = if "s[i-1]+s[i]" is >= 10 and <= 26 : += dp[i-2]
//        = if "s[i]" is > 0  : += dp[i-1]