/// Severity: Sev0
// Date: 20Feb26
// LC: 2842
// Where I failed: algo
// Pattern: greedy
// Notes: hard..mathmod



class Solution {
public:
    int mod = 1e9+7;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        
        vector<int> cnt(26,0);
        for(auto c:s)cnt[c-'a']++;
        sort(cnt.begin(),cnt.end(),[](int& i1, int& i2){ return i1>i2; });
        long ans = 1;
        for(auto i=0;i<26 && k;i++){
            if(cnt[i] == 0)return 0;
            int freq = cnt[i++], cur = 1;
            while((i<26) && (cnt[i] == cnt[i-1])) {
                cur++;
                i++;
            }
            i--;
            if(cur <= k){
                ans = (ans * mypow(freq,cur))%mod;
                k-=cur;
            } else {
                ans = ((ans * ncr(cur,k) )%mod* mypow(freq,k))%mod;
                k=0;
                break;
            }
        }
        return k ? 0 :ans;
    }
    int ncr(int n,int r){
        if(r == 0) return 1;
        if(r==1) return n;
        return ncr(n-1,r-1) * n / r;
    }

    int mypow(int x, int y){
        long ans = 1;
        while(y--){
            ans = (ans * x)%mod;
        }
        return ans;
    }
};