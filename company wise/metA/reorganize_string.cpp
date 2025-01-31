
// 22 jan 2025..
// 10 mins..
// 2 logical error..
// couldnt think of optimal solution..
// verdict : FAIL

class Solution {
public:
    string reorganizeString(string s) {
        vector<int> cnt(26,0);
        int maxCh = -1, maxCnt = 0;
        for(auto& c: s){
            cnt[c-'a']++;
            if(maxCnt < cnt[c-'a']){
                maxCnt = cnt[c-'a'];
                maxCh = c-'a';
            }
        }
        int n = s.size(), idx = 0;
        string ans = string(n,'.');
        if(maxCnt > (n+1)/2)return "";

        while(cnt[maxCh]){
            ans[idx] = 'a'+maxCh;
            idx += 2;
            cnt[maxCh]--;
        }

        for(auto i=0;i<26;i++){
            while(cnt[i]){
                cnt[i]--;
                if(idx>=n){
                    idx = 1;
                }
                ans[idx] = 'a'+i;
                idx +=2;
            }
        }
        return ans;
    }
};

