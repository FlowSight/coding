// 11 feb26
// sev2..missed corner case.. implemented rabin karp
// sev0: could not thnk most optimized: lee's approach

class Solution {
public:
    vector<int> dp;
    vector<long> exp;
    int mod = 1e9+7;
    int longestDecomposition(string text) {
        int n = text.size();
        dp = vector<int>(n,-1);
        for(auto i=0;i<n/2;i++)exp.push_back(exp.size()?(exp.back()*26)%mod:1);
        helper(text,0);
        return dp[0];
    }

    int helper(string& str, int idx){
        int n = str.size(), ans = 1, len = 1, start = idx, left = idx, right = n-idx-1;
        if(idx>=n) return 0;
        long prefHash = 0, sufHash = 0;
        if((left > right)) return dp[left] = 0;
        if(dp[idx] != -1) return -1;
        while(left<right){
            prefHash = (prefHash*26 + str[left]-'a')%mod;
            sufHash = (sufHash + exp[left-start]*(str[right]-'a'))%mod;
            if(prefHash == sufHash){
                auto pref = str.substr(start,len), suf = str.substr(right,len);
                if(pref == suf) {
                    ans = max(ans,2+helper(str,left+1));
                }
            }
            left++;
            right--;
            len++;
        }
        return dp[start] = ans;
    }
};


//lee
    int longestDecomposition(string S) {
        int res = 0, n = S.length();
        string l = "", r = "";
        for (int i = 0; i < n; ++i) {
            l = l + S[i], r = S[n - i - 1] + r;
            if (l == r)
                ++res, l = "", r = "";
        }
        return res;
    }