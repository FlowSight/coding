/// Severity: Sev2
// Date: 17Feb26
// 
// How much solved: Fully
// Where I failed: getting the concept..had hint from solution + corner case
// Pattern: backtrack with bm

class Solution {
public:
    string minAbbreviation(string target, vector<string>& dict) {
        int n = target.size(), cnt = 0, ansLen = INT_MAX, len = 0;
        string cur = "", ans = "";
        unordered_set<string> ss;
        for(auto it : dict){
            if(it.size() != n) continue;
            for(auto bm=0;bm<(1<<n);bm++){
                cur = "";
                cnt = 0;
                for(auto i=0;i<n;i++){
                    if(bm & (1<<i)) {
                        if(cnt) cur += to_string(cnt);
                        cnt = 0;
                        cur.push_back(it[i]);
                    } else cnt++;
                }
                if(cnt) cur += to_string(cnt);
                ss.insert(cur);
            }
        }
        for(auto bm=0;bm<(1<<n);bm++){
            cur = "";
            cnt = 0, len = 0;
            for(auto i=0;i<n;i++){
                if(bm & (1<<i)) {
                    if(cnt) {
                        len++;
                        cur += to_string(cnt);
                    }
                    cnt = 0;
                    cur.push_back(target[i]);
                    len++;
                } else cnt++;
            }
            if(cnt) {
                cur += to_string(cnt);
                len++;
            }
            if(ss.find(cur) != ss.end()) continue;
            if(len < ansLen) {
                ansLen = len;
                ans = cur;
            }
        }
        return ans;
    }
};
