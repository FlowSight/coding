// 11 mar 2025
// 16 min..
// 1 compiler error
// sev2

class Solution {
    public:
        int eraseOverlapIntervals(vector<vector<int>>& intervals) {
            vector<int> last = {-600000,-600000};
            sort(intervals.begin(),intervals.end(),[](const vector<int>& v1, const vector<int>& v2){
                return v1[0] == v2[0] ? v1[1] < v2[1] : v1[0]<v2[0]; 
            });
            int ans = 0;
            for(auto it: intervals){
                if(it[0] >= last[1]){
                    last = it;
                } else {
                    ans++;
                    if(it[1]<= last[1]){
                        last = it;
                    }
                }
            }
            return ans;
        }
    };
