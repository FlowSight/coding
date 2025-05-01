// 26 apr 2025.
// 1 compiler + 1 logical mistake..
// sev1

class Solution {
    public:
        bool carPooling(vector<vector<int>>& trips, int capacity) {
            map<int,long> mm;
            long long cur = 0;
            for(auto &it : trips){
                mm[it[1]] += it[0];
                mm[it[2]] -= (it[0]);
            }
            for(auto it : mm){
                cur += it.second;
                if(cur > (long)capacity) return false;
            }
            return true;
        }
    };