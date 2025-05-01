// 24 apr 2025
// 5 min..clean
// there is a O(1) space solution for this problem
class Solution {
    public:
        unordered_map<int,vector<int>> mm;
        Solution(vector<int>& nums) {
            int n = nums.size();
            for(auto i=0;i<n;i++){
                mm[nums[i]].push_back(i);
            }
        }
        
        int pick(int target) {
            auto& val = mm[target];
            int idx = rand()%(val.size());
            return val[idx];
        }
    };

    // reservoir sampling has a solution where k==1