// LC : 1994
class Solution {
public:
    typedef vector<int> vi;
    unordered_map<int,int> powdp;
    vi primes = { 2,3,5, 7, 11, 13, 17, 19, 23, 29};
    int mod = 1e9+7;
    int numberOfGoodSubsets(vector<int>& nums) {
        int reqbm = (1<<10)-1;
        unordered_map<int,int> cnt;
        vector<long> dp(reqbm+1,0);
        dp[0] = 1;
        for(auto it : nums)cnt[it]++;
        for(auto i=2;i<=30;i++ ){
            if((cnt.find(i) == cnt.end()) || (i%4==0) || (i%9 == 0) || (i==1) || (i%25 == 0)) continue;
            int curbm = getbm(i);
            for(auto j=0;j<=reqbm;j++){
                if(j & curbm) continue;
                int tmp = curbm | j;
                dp[tmp] = (dp[tmp] + (dp[j]*cnt[i])%mod)%mod;
            }
        }
        //cout<<"ok";
        long ans = -1, pow2 = mypow(cnt.find(1) == cnt.end() ? 0 : cnt[1]);
        for(auto it : dp) {
            ans = (ans + (it))%mod;
        }
        return (ans * pow2)%mod;
    }
    int getbm(int num){
        int ans = 0;
        for(auto i=0;i<10;i++){
            if(num %primes[i] == 0) ans = (ans | (1<<i));
        }
        return ans;
    }
    long mypow(int x){
        if(x==0) return 1;
        if(x == 1) return 2;
        if(powdp.find(x) != powdp.end()) return powdp[x];
        if(x & 1){
            return powdp[x] = (2 * mypow(x-1))%mod;
        }
        long tmp = mypow(x/2);
        return powdp[x] = (tmp*tmp) % mod;
    }
};
