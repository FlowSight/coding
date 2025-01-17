// 18 dec..6 min..no mistake
// verdict : pass
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,vector<int>> mm;
        int n = nums.size();
        for(auto i=0;i<n;i++){
            mm[nums[i]].push_back(i);
        }
        for(auto &it : mm){
            int rem = target - it.first;
            if((rem == it.first )&& (it.second.size() == 1)) continue;
            if(mm.find(rem) == mm.end()) continue;
            return {it.second.back(),mm[rem][0]};
        }
        return {-1,-1};
    }


// 1 nov..
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int,vector<int>> mm;
        for(auto i=0;i<n;i++){
            if(mm.find(target-nums[i]) != mm.end()) return {i,mm[target-nums[i]][0]};
            mm[nums[i]].push_back(i);
        }
        return {-1,-1};
    }
};

// fucked up corner case