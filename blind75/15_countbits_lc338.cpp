    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(auto i=0;i<=n;i++){
            dp[i] = dp[i>>1] + (i&1);
        }
        return dp;
    }
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(auto i=1,exp = 1;i<=n;i++){
            if(exp*2 == i)exp*=2;
            dp[i] = dp[i-exp] + 1;
        }
        return dp;
    }