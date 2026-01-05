// sev0..could not come up
// 14/12/25

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        vvi arr;
        int n = nums1.size(), sum1 = 0, sum2 = 0;
        for(auto i=0;i<n;i++) {
            sum1 += nums1[i];
            sum2 += nums2[i];
            arr.push_back({nums1[i],nums2[i]});
        }
        if(sum1<=x) return 0;
        sort(arr.begin(),arr.end(),[](vi& v1, vi& v2){
            return v1[1] < v2[1];
        });
        vvi dp(n+1,vi(n+1,-1));
        for(auto i=0;i<=n;i++) dp[i][0] = 0;
        for(auto j=1;j<=n;j++){
            for(auto i=1;i<=n;i++){
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-1] + arr[i-1][0] + arr[i-1][1]*(j)); 
            }
            if(sum1 + sum2*j - dp[n][j] <= x) return j;
        }
        return -1;
    }
};

// dp[i][j] =  max score can be reduced by applying j ops upto i
// sum1 + sum2*t - dp[n][t] <= x