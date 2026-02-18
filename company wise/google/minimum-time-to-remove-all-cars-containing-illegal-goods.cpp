/// Severity: Sev0..sev0
// Date: 16Feb26
// 
// How much solved: Fully
// Where I failed: algo
// Pattern: kadane

class Solution {
public:
    int minimumTime(string s) {
        int n = s.size(), cur = 0, ans = 0;
        for(auto i=0;i<n;i++){
            int num = s[i] == '0' ? -1 : 1;
            cur += num;
            ans = min({ans,num,cur});
            if(cur >=0) cur = 0;
        }
        return n + ans;
    }
};

