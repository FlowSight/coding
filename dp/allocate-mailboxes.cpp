/// Severity: Sev0
// Date: 18May26
// LC: 1478
// Where I failed: algo..could not get dp state..
// Pattern: dp..2d..divide whole arr into K  buckets ..place at median
// Notes: sev0..sev00



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi cost, dp;
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        sort(houses.begin(), houses.end());
        cost = vvi(n,vi(n,0));
        dp =  vvi(n+1,vi(k+1,1e6));
        for(auto i=0;i<n;i++){
            for(auto j=i;j<n;j++){
                int med = (j+i)/2;
                for(auto k=i;k<=j;k++){
                    cost[i][j] += abs(houses[med]-houses[k]);
                }
            }
        }
        dp[0][0] = 0;
         for(auto i=1;i<=n;i++){
            for(auto j=1;j<=k;j++){
                if(i < j) break;
                for(auto kk = i;kk>=1;kk--){
                    dp[i][j] = min(dp[i][j], dp[kk-1][j-1] +cost[kk-1][i-1]);
                }
            }
         }
        return dp[n][k];
    }
};


// .....i...

// dp[i][j] = till house i, putting j mailbox, min costm=
//     min (dp[i-1][j]+curcost, dp[i-1][j-1])

// 1 3 5 7 8 11
//  2 2 2 1 3
//  2 4 6 7 10

