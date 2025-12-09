//sev2..corner case missed.8/12/25

class SummaryRanges {
public:
    map<int,int> mm;
    SummaryRanges() {
        mm.clear();
    }
    
    void addNum(int value) {
        if(mm.size() == 0){
            mm[value] = value;
            return;
        }
        auto it = mm.upper_bound(value);
        if((it != mm.begin()) && (prev(it)->second >= value)) return;
        // its not in any range
        // it is > val, or end, prev(it)->second is < than val
        mm[value] = value;
        int left = value, right = value;
        it = mm.find(value);
        if((it != mm.begin()) && (prev(it)->second+1 == value)) {
            left = min(left,prev(it)->first);
            right = max(right,prev(it)->second);
            mm.erase(prev(it));
        }
        if((it != mm.end()) && (next(it)->first-1 == value)) {
            left = min(left,next(it)->first);
            right = max(right,next(it)->second);
            mm.erase(next(it));
        }
        mm.erase(value);
        mm[left] = right;
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>>  ans;
        for(auto it : mm){
            ans.push_back({it.first,it.second});
        }
        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

//  [1,4] [7,7] [9,12]
//     6

//  [3,4] [7,7] [9,12]
//     5
// [1,4] 
//     6