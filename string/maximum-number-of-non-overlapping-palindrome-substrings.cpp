/// Severity: Sev1
// Date: 20Aug26
// LC: 2472
// Where I failed: corner case of ispalin
// Pattern: ispalin
// Notes: additional_notes




class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int maxPalindromes(string s, int k) {
        int n = s.size(), ans = 0;
        if(k==1) return n;
        vvi ispalin(n,vi(n,0));
        for(auto i=0;i<n;i++){
            ispalin[i][i] = 1;
            if((i+1 < n) && (s[i] == s[i+1])) ispalin[i][i+1] = 1;
        }
        for(auto len = 3;len<=n;len++){
            for(auto i=0,j = i+len-1; j<n;i++,j++){
                ispalin[i][j] = ispalin[i+1][j-1] && (s[i] == s[j]);
            }
        }
        vi dp(n,0);
        for(auto j=k-1;j<n;j++){
            dp[j] = max(dp[j],dp[j-1]);
            for(auto i=j-(k-1);i>=0;i--){
                if(ispalin[i][j]) {
                    dp[j] = max(dp[j], 1 + (i ? dp[i-1] : 0));
                    break;
                }
            }
            
            ans = max(ans,dp[j]);
        }
        return ans;
    }
};