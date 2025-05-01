// 23 apr 2025
// completely failed..
// got one hint..took that to completion..still some index issues.
// sev0

class Solution {
    public:
        long long countGood(vector<int>& nums, int k) {
            long long ans = 0,  n = nums.size(), cur = 0;
            unordered_map<int,int> mm;
            for(auto l=0,r=0;r<n;r++){
                cur += (mm.find(nums[r]) == mm.end() ? 0 : mm[nums[r]]) ;
                mm[nums[r]]++;
                while(cur>=k) {
                    mm[nums[l]]--;
                    cur -= max(0,mm[nums[l++]]);
                }
                ans += l;
            }
            return ans;
        }
    };

    