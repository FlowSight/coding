/// Severity: Sev0..sev0..sev0.
// Date: 24May26
// LC: 3405
// Where I failed: hole first, modinverse
// Pattern: maths, perm/comb
// Notes: additional_notes

class Solution {
public:
    typedef vector<long> vi;
    typedef vector<vi> vvi;
    int mod = 1e9+7;
    vi fact;
    int countGoodArrays(int n, int m, int k) {
        fact = vi(n+1,1);
        for(auto i=2;i<=n;i++){
            fact[i] = (fact[i-1]*i)%mod;
        }
        long pw = mypow(m-1,n-k-1);
        return ((m*pw)%mod * ncr(n-1,k))%mod;
    }

    int ncr(int n, int r){
        long long num = fact[n], denom = (fact[n-r] * fact[r])%mod;
        return ((long long)num*mypow(denom,mod-2))%mod;
    }

    int mypow(long long x, long long y) {
        long long res = 1;
        x %= mod;
        while(y > 0) {
            if(y & 1) res = res * x % mod;
            x = x * x % mod;
            y >>= 1;
        }
        return res;
    }
};

