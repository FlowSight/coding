// LC : 2008

// 18apr2026
// sev0 : almost got it, except the continuous part..cant use map which is sparse

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        sort(rides.begin(),rides.end(),[](vi& v1, vi& v2){
            return v1[0] == v2[0] ? v1[1] < v2[1] : v1[0] < v2[0];
        });
        vector<long long> dp(n+1,0);
        long  long ans = 0, idx = 0, mod = 1e9+7;
        for(auto i=1;i<=n;i++){
            dp[i] = max(dp[i],dp[i-1]);
            while((idx<rides.size()) && (rides[idx][0] == i)){
                int start = rides[idx][0], end = rides[idx][1], earn = end-start+rides[idx][2];
                dp[end] = max(dp[end],(dp[start] + earn)); 
                idx++;
            }
        }
        return dp[n];
    }
};
