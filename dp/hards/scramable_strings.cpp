/// Severity: Sev0
// Date: 03Jun26
// LC: 87
// Where I failed: algo
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    vvvi dp;
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        dp = vvvi(n,vvi(n,vi(n+1,-1)));
        return helper(s1,s2,0,0,n);
    }
    bool helper(string& s1, string& s2, int l1, int l2, int len){
        if(l1+len-1 >= s1.size()) return false;
        if(l2+len-1 >= s2.size()) return false;
        if(len == 1) return s1[l1] == s2[l2];

        if(dp[l1][l2][len] != -1) return dp[l1][l2][len];

        // prune
        vi cnt(26,0);
        int r1 = l1+len-1, r2 = l2+len-1;
        for(auto i1=l1,i2 = l2;(i1<=r1) && (i2 <= r2);i1++,i2++){
            cnt[s1[i1]-'a']++;
            cnt[s2[i2]-'a']--;
        }
        for(auto i=0;i<26;i++) {
            if(cnt[i]) return dp[l1][l2][len] = false;
        }

        for(auto i=1;i<len;i++){
            if(helper(s1,s2,l1,l2,i) && helper(s1,s2,l1+i,l2+i,len-i)) return dp[l1][l2][len] = true;
            if(helper(s1,s2,l1,r2-i+1,i) && helper(s1,s2,l1+i,l2,len-i)) return dp[l1][l2][len] = true;
        }
        return dp[l1][l2][len] = false;
    }
};


astoria :
grand palace : written conflicting details, said allowed
sv international : said no, written allowed but need proof of couple
snooze inn :didnt call, written not allowed