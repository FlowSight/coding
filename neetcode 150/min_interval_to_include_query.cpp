// 13 mar 2025
// got a convoluted approach..but not quite elegant..took 30 min to implement..instead i saw the sol..
// sev0

class Solution {
    public:
        vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
            vector<int> queriesCopy = queries, ans = {};
            sort(intervals.begin(),intervals.end());
            sort(queries.begin(),queries.end());
    
    
            set<pair<int,int>> ss;
            unordered_map<int,int> mm;
            int idx = 0, n = intervals.size();
            for(auto q: queries){
                while((idx<n) && (intervals[idx][0] <= q)) {
                    auto l = intervals[idx][0] , r = intervals[idx++][1];
                    ss.insert({r-l+1,r});
                }
                while(!ss.empty() && (ss.begin()->second < q )){
                    ss.erase(ss.begin());
                } 
                if(!ss.empty()){
                    mm[q] = ss.begin()->first;
                } else {
                    mm[q] = -1;
                }
            }
            for(auto it : queriesCopy){
                ans.push_back(mm[it]);
            }
            return ans;
        }
    };

    //  another genius idea is to sort intervals by size..and the queries..then loop over intervals..
    //     -> binary search in queries to  get l,r -> loop over l to r and make par[l] = l+1 -> union find..