// 16 jan 2025.. 
// 1 logical mistake ... didnt do logically correct code at start..didnt dry run..
// verdict : FAIL

    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end());
        vi dp(amount+1,amount+1);
        dp[0] = 0;
        int n = coins.size();
        for(auto i = 1;i<=amount;i++){
            for(auto j=0;j<n;j++){
                if(coins[j]>i)break;
                dp[i] = min(dp[i],dp[i-coins[j]]+1);
            }
        }
        return dp[amount] >= amount+1 ? -1 : dp[amount];
    }

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int coinChange(vector<int>& coins, int money) {
        sort(coins.begin(),coins.end());
        int n = coins.size();
        vi dp(money+1,1e4+1);
        dp[0] = 0;

        for(auto i=1;i<=money;i++){
            for(auto c : coins) {
                if( c > i)break;
                dp[i] = min(dp[i], dp[i-c]+1);
            }
        }
        return dp[money] == 1e4+1 ? -1 : dp[money];
    }
};

// dp[i][j] = mim how many coins needed to  make amount i with j coins
