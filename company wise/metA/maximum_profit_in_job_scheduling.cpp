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

// We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

// You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

// If you choose a job that ends at time X you will be able to start another job that starts at time X.