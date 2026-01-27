// 26jan2026
// sev0...sev0...could not think of kmp, impelemtation mistake rolling hash



class Solution {
public:
    long mod = 1e9+7, coef = 256, runningCoef = 1;
    string longestPrefix(string s) {
        //rolling hash
        int preHash = 0, sufHash = 0, n = s.size(),ans = 0;
        for(auto i=0;i<n-1;i++){
            preHash = (preHash*coef + (s[i]))%mod;
            sufHash = (sufHash + (s[n-1-i])*runningCoef)%mod;
            runningCoef = (runningCoef*coef)%mod;
            if(sufHash == preHash) {
                for(auto j=0;j<=i;j++)if(s[j] != s[n-1-j]) continue;
                ans = i+1;
            }
        }
        return s.substr(0,ans);
    }
};
//then there is textbook kmp
