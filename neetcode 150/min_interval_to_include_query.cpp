// 30 apr 2025..
// go a new approach..didnt remember the old one..sev3


// my approach
class Solution {
    public:
        vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
            sort(intervals.begin(),intervals.end(),[](vector<int>& v1, vector<int>& v2) {
                return v1[1]-v1[0] < v2[1]-v2[0];
            });
            set<int> ss;
            unordered_map<int,int> mm;
            for(auto q : queries)ss.insert(q);
            for(auto it : intervals){
                auto l = it[0], r = it[1];
                auto ll = ss.lower_bound(l);
                auto rr = ss.upper_bound(r);
                for(auto it = ll;it != rr;it++){
                    mm[*(it)] = r-l+1;
                }
                ss.erase(ll,rr);
            }
            vector<int>  ans;
            for(auto q : queries){
                ans.push_back(mm.find(q) == mm.end() ? -1 : mm[q]);
            }
            return ans;
        }
    };
    


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