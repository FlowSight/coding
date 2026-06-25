// i could do below
class Solution {public:
    int twoEggDrop(int n) {
        if(n <= 2)return n;
        vector<int> dp(n+1,n);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(auto i=3;i<=n;i++){
            for(auto j=1;j<i;j++){
                dp[i] = min(dp[i],1+max(j-1,dp[i-j]));
            }
            costForCur = 1+max(i-1,dp[i])
        }
        return dp[n];
    }
};

but if the optimal answer is x, then first i have to try at xth floor as
 break : 1 + x-1 tries 
 not break : remaining with n-x floors : recursive..


 
ax^2 + bx + c = 0
(-b + sqrt(b^2 - 4ac))/2