// 12 feb 2025
// 14 mins.
// 1 compiler error 
// sev2
// verdict : FAIL

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> cnt(26,0), cnt1(26,0);
        int n2 = s2.size(), n1 = s1.size();
        for(auto c: s1) cnt[c-'a']++;

        for(auto l=0,r=0;r<n2;r++) {
            cnt1[s2[r]-'a']++;
            if(r-l+1 > n1){
                cnt1[s2[l++]-'a']--;
            }
            if (same(cnt,cnt1)) return true;
        } 
        return false;
    }

    bool same(vector<int>& cnt1, vector<int>& cnt2){
        for(auto i=0;i<26;i++){
            if(cnt1[i] != cnt2[i]) return false;
        }
        return true;
    }
};
