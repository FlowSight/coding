/// Severity: Sev3
// Date: 08Aug26
// LC: 1359
// Where I failed: none
// Pattern: AP series
// Notes: additional_notes



class Solution {
public:
    int countOrders(int n) {
        long last = 1, mod = 1e9+7, ans = 1;
        for(auto i = 2;i<=n;i++){
            auto cur = 2*(i-1);
            last = (last + (2*cur + 1))%mod;
            ans = (ans * last) %mod;
        }
        return ans;
    }
};

