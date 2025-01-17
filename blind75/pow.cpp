// 2 jan 2025
// did see constaints after coding initial draft..should have done earlier..
// missed INT_MIN/MAX case
// verdict : FAIL

class Solution {
public:
    unordered_map<int,double> dp;
    double myPow(double x, int n) {
        if(x==0.0)return 0.0;
        if(n==0) return 1;
        if(n<0){
            n = abs(n+1);
            return (double)1.0/(x*myPow(x,n));
        }
        if(n==1)return x;
        auto tmp = (dp.find(n/2) != dp.end())?dp[n/2]:myPow(x,n/2);
        dp[n] = tmp*tmp*(n%2?x:1);
        return dp[n];
    }
};
