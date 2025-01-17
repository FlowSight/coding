https://leetcode.com/problems/construct-string-with-repeat-limit/description/?envType=daily-question&envId=2024-12-17



// 18 dec 2024..22 min..didnt read qs exactly
// didnt dry run..
// logical mistake in code..(TODO)
// Verdict : FAIL

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        int n = s.size();
        string ans = "";
        vector<int> cnt(26,0);
        for(auto c : s)cnt[c-'a']++;
        for(auto i=25,j=0;i>=0;i--,j=0){
            while(cnt[i] && (j<repeatLimit)) {
                ans.push_back('a'+i);
                cnt[i]--;
                j++;
            }
            if(cnt[i]) {
                int found = -1;
                for(auto k=i-1;k>=0;k--){
                    if(cnt[k]) {
                        found = k;
                        break;
                    }
                }
                if(found != -1){
                    ans.push_back(found+'a');
                    cnt[found]--;

                } else {
                    cnt[i] = 0;
                }
                i++;
            }
        }
        return ans;
    }
};
