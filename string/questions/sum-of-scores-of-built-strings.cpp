/// Severity: Sev0
// Date: 15May26
// LC: 2223
// Where I failed: algo
// Pattern: z algo
// Notes: sev0..sev0..sev0..



class Solution {
public:
    long long sumScores(string s) {
        int n = s.size(), l = 0, r = 0;
        long long ans = 0;
        vector<int> zscore(n,0);
        for(auto i=1;i<n;i++){
            if(i<=r) zscore[i] = min(r-i+1,zscore[i-l]);
            while((i+zscore[i]<n) && (s[zscore[i]] == s[i+zscore[i]])) zscore[i]++;
            if(i+zscore[i]-1 > r) {
                l = i;
                r = i+zscore[i]-1;
            }
            ans += zscore[i];
        }
        return ans+n;
    }
};