// completely beaten...could not think..eularian path
// missed the main catch : greedily taking doesnt guarantee the correct path..we need minimal AS WELL AS the correct path
// 25 mar 2025
// sev0

class Solution {
    public:
        vector<string> ans;
        unordered_map<string,multiset<string>> g;
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            for(auto it : tickets){
                g[it[0]].insert(it[1]);
            }
            helper("JFK");
            reverse(ans.begin(),ans.end());
            return ans;
        }
    
        void helper(string cur){
            while(g[cur].size() > 0) {
                auto next = *(g[cur].begin());
                g[cur].erase(g[cur].begin());
                helper(next);
            }
            ans.push_back(cur);
        }
    };