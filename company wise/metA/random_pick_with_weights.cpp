// 21 apr 2025..
// i fucked up in lower bound code..
// then fucked up in spiral..
// sev0 sev0 sev0

// 1 jan 2025
// 10 mins..
// logic mistake..returned number instead of index..
// verdict : FAIL
// TODO : read https://leetcode.com/problems/random-pick-with-weight/solutions/671439/python-smart-o-1-solution-with-detailed-explanation/

class Solution {
public:
    vector<int> preSum;
    int tot, n;
    Solution(vector<int>& w) {
        tot = 0;
        n = w.size();
        for(auto &it : w){
            preSum.push_back(tot=tot+it);
        }
    }
    
    int pickIndex() {
        int idx = rand()%tot;
        int l = 0, r = n-1, mid = 0;
        while(l<r){
            if(l+1 == r) {
                if(preSum[l]>=idx+1) return l;
                return r;
            }
            mid = (l+r)/2;
            if(preSum[mid] < idx+1) l = mid+1;
            else r = mid;
        }
        return l;
    }
};