// damn, could not think this way..
// ifany no is >n, regenerate from the no before it...this is essentially backtracking
// severity : sev0

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<vector<int>> combine(int n, int k) {
        vi cur(k,0);
        vvi ans = {};
        int idx = 0;
        while(idx>=0){
            cur[idx]++;
            if(cur[idx] > n) idx--;
            else if(idx == k-1) {
                ans.push_back(cur);
            } else {
                idx++;
                cur[idx]=cur[idx]-1;
            }
        }
        return ans;
    }
};

