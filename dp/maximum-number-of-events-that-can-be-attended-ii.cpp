/// Severity: Sev0
// Date: 25May26
// LC: 1751
// Where I failed: algo..complicated..i though starttime has be i in dp[i], but
// i can be actual index..
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(),events.end(),[](vector<int>& v1, vector<int>& v2){
            return v1[1]<v2[1];
        });
        int n = events.size(), ans = 0;
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        // one more optimization is, for each i, have bsidx[i] = lower bound for events[i][0] ....O(nlogn)
        // then below loop is O(nk)..ttoal = O(n(logn + k))
        for(auto i=1;i<=k;i++)dp[0][i] = INT_MIN;
        for(auto i=1;i<=n;i++){
            for(auto j=1;j<=k;j++){
                if(j>i) dp[i][j] = INT_MIN;
                else {
                    int idx = binsearch(events,i-1, events[i-1][0]);
                    dp[i][j] = max({0,dp[i-1][j], dp[idx+1][j-1] + events[i-1][2]});
                    ans = max(ans,dp[i][j]);
                }
            }
        }
        return ans;
    }

    int binsearch(vector<vector<int>>& arr, int r, int num){
        int n = arr.size(), l = 0, mid = 0;
        while(l<r){
            if(l+1 == r){
                return arr[r][1] < num  ? r: arr[l][1] < num ? l :-1;
            }
            mid = (l+r)/2;
            if(arr[mid][1] < num) l = mid;
            else r = mid-1;
        }
        return arr[l][1] < num ?  l : -1;
    }
};

// dp[i][j] = 0 to i...taking j events