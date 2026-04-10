// LC : 759

class Solution {
public:
    typedef vector<int> vi;
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        set<vi> ss;
        vector<Interval> ans;
        int n = schedule.size();
        for(auto i=0;i<n;i++){
            ss.insert({schedule[i][0].start,i,0});
        }
        int prev = (*(ss.begin()))[0];
        while(!ss.empty()){
            auto tp = *(ss.begin());
            ss.erase(ss.begin());
            int curs = tp[0], idx = tp[1], idx1 = tp[2];
            if(curs > prev) ans.push_back(Interval(prev,curs));
            prev = max(prev,schedule[idx][idx1].end);
            idx1++;
            if(idx1 < schedule[idx].size()) ss.insert({schedule[idx][idx1].start,idx,idx1});
        }
        return ans;
    }
};