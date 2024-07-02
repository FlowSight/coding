class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int open = newInterval[0], close = newInterval[1], idx = 0, n = intervals.size();
        for(auto it : intervals){
            if(isDisjoint(open,close,it)){
                if((it[0] > close) && (close != -1)){
                    ans.push_back({open,close});
                    close = -1;
                }
                ans.push_back(it);
            } else {
                open = min({open,it[0]});
                close = max({close,it[1]});
            }
        }
        if((close != -1)){
            ans.push_back({open,close});
        }

        return ans;
    }
    bool isDisjoint(int& open, int& close, vector<int>& interval){
        return (open >interval[1]) || (close < interval[0]);
    }
};

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int open = newInterval[0], close = newInterval[1], idx = 0, n = intervals.size();
        while(idx <n && intervals[idx][1] < open)ans.push_back(intervals[idx++]);
        while(idx <n && !isDisjoint(open,close,intervals[idx])){
            open = min({open,intervals[idx][0]});
            close = max({close,intervals[idx][1]});
            idx++;
        }
        ans.push_back({open,close});
        while(idx <n)ans.push_back(intervals[idx++]);
        return ans;
    }
    bool isDisjoint(int open, int close, vector<int> interval){
        return (open >interval[1]) || (close < interval[0]);
    }
};