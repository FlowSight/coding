// if s2 is substr of s1.
    bool isSubstrRabinKarp(string& s1, string& s2) {
        long targetHash = 0, curHash = 0;
        int m = s1.size(), n = s2.size();
        vector<long> exp(n,1);
        for(auto i=1;i<n;i++){
            exp[i] = (exp[i-1]*256)%mod;
        }
        for(auto i=0;i<n;i++){
            targetHash  = ((targetHash*256)%mod + (int)s2[i])%mod;
        }
        for(auto i=0;i<m;i++){
            if(i>=n) {
                curHash  = ( curHash - (s1[i-n]*exp[n-1])%mod + mod)%mod;
            }
            curHash  = ((curHash*256)%mod + (int)s1[i])%mod;
            if(curHash == targetHash){
                int match = 1, k = 0;
                for(auto j=i-n+1;j<=i;j++){
                    if(s1[j] != s2[k++]){
                        match = 0;
                        break;
                    }
                }
                if(match)return true;
            }
        }
        return false;
    }
