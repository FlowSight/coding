/// Severity: Sev0
// Date: 30Jul26
// LC: 1589
// Where I failed: description
// Pattern: diff array, greedy
// Notes: additional_notes



class Solution {
public:
    int mod = 1e9+7;
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& reqs) {
        sort(nums.begin(),nums.end());
        map<int,int> mm;
        map<long,vector<int>> mm1;
        for(auto& it : reqs) {
            mm[it[0]]++;
            mm[it[1]+1]--;
        }
        long cur = 0, idx = nums.size()-1, ans = 0;
        for(auto it : mm){
            mm1[cur].push_back(it.first-1);
            cur += it.second;
            mm1[cur].push_back(it.first);
        }
        for(auto it = mm1.rbegin(); it != mm1.rend();it++){
            if(it->first == 0) continue;
            for(auto i=0;i<it->second.size();i+=2){
                auto l = it->second[i], r = it->second[i+1], cnt = r -l +1;
                while(cnt){
                    ans = (ans +  (it->first * nums[idx--])%mod )%mod ;
                    cnt--;
                }
            }
        }
        return ans;
    }
};


// (0,1) (1,3)
// { 0 : 1 , 1: 1, 2: -1, **4 : -1 }
// cur = 0;

// 0 : (-1,)
// 1 : (0,0,2,3)
// 2 : (1,1)


