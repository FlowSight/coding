//sev2 14nov25..
// minor implementation bug..
// did not come up with line sweep algo (TODO)
// ans[i] = flowers started blooming before or at i - flowers stopped blooming before or at i

class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        map<int,int> mm;
        unordered_map<int,vector<int>> idxMap;
        int n = people.size(), idx = 0, cur = 0;
        vector<int> ans(n,0);
        for(auto it : flowers) {
            mm[it[0]]++;
            mm[it[1]+1]--;
        }
        for(auto i=0;i<n;i++) idxMap[people[i]].push_back(i);
        sort(people.begin(), people.end());
        for(auto it : mm){
            while((idx<n) && (people[idx]<it.first)) {
                for(auto it1:idxMap[people[idx]]) ans[it1] = cur;
                idx++;
                while((idx<n) && (people[idx] == people[idx-1])) idx++;
            }
            cur+=it.second;
            while((idx<n) && (people[idx]==it.first)) {
                for(auto it1:idxMap[people[idx]]) ans[it1] = cur;
                idx++;
                while((idx<n) && (people[idx] == people[idx-1])) idx++;
            }
        }
        return ans;
    }
};