8 june 2025
// had a few hiccups..tried with diff data structures..



class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size(), ans = 0;
        set<int> ss;
        unordered_map<int,vector<int>> endMap;
        unordered_map<int,int> ansMap;
        for(auto i=0;i<n;i++) {
            ss.insert(startTime[i]);
            ss.insert(endTime[i]);
            endMap[endTime[i]].push_back(i);
        }
        for(auto it : ss) {
            if(endMap.find(it) != endMap.end()) {
                for(auto jobIdx : endMap[it]) {
                    int jobStart = startTime[jobIdx];
                    ans = max(ans,ansMap[jobStart]+profit[jobIdx]);
                }
            }
            ansMap[it] = ans;
        }
        return ans;
    }
};