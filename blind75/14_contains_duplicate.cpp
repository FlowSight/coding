// 18 dec 2024 .. 1 min..again made compiler errror...
// verdict : FAIL

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mm;
        for(auto &it : nums){
            mm[it]++;
            if(mm[it] == 2)return true;
        }
        return false;
    }
};