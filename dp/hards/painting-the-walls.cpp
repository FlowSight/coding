/// Severity: Sev0..sev0..sev0..Sev0..sev0..sev0..Sev0..sev0..sev0
// Date: 15Jun26
// LC: 2742
// Where I failed: deduction into coin change, coin change 1d dp
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    int maxlim = 1e9;
    typedef vector<int> vi;
    vi dp;
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        dp = vi(n+1,maxlim);
        dp[0] = 0;
        for(auto i=0;i<n;i++){
            for(auto j=n;j;j--){
                dp[j] = min(dp[j],cost[i]+dp[max(0,j-time[i]-1)]);
            }
        }
        return dp[n];
    }
};


class Solution {
public:
    int maxlim = 1e9;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        dp = vvi(n,vi(n+1,maxlim));

        // i messed up this base case.
        for(auto i=0;i<n;i++) dp[i][0] = 0;
        for(auto j=1; j<=min(n, time[0]+1); j++) dp[0][j] = cost[0];

        for(auto i=1;i<n;i++){
            for(auto j=1;j<=n;j++){
                dp[i][j] = min(dp[i-1][j]  , cost[i]+dp[i-1][max(0,j-time[i]-1)]);
            }
        }
        return dp[n-1][n];
    }
};




