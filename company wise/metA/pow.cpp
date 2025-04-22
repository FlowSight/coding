// 20 apr 2025
// messed up big time..too many corner case...
// sev0 sev0 sev0

class Solution {
    public:
        unordered_map<double,double> dp;
        double myPow(double x, int n) {
            if((n == 0)) return 1.0;
            if(x == 0) return 0;
            if(n <0) {
                if(n == INT_MIN) return (double)1/myPow(x,-(n+1))*(1/x);
                return (double)1/myPow(x,-n);
            }
            if(n == 1) return x;
            if(dp.find(n) != dp.end()) return dp[n];
            auto half = myPow(x,n/2);
            auto ans = half * half;
            if(n%2) ans = ans*x;
            return dp[n] = ans;
        }
    };
    
    // x^n = x^(n/2 + n/2 + n%2)
    //     = x^(n/2) * x^(n/2) * x(if n%2)