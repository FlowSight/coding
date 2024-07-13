    class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            sort(nums.begin(),nums.end());
            vector<vector<int>> ans;
            int n = nums.size();
            for(auto i=0;i<n;i++){
                if(i && (nums[i] == nums[i-1]))continue;
                int l = i+1, r = n-1, target = -nums[i];
                while(l<r){
                    if(nums[l]+nums[r] > target)r--;
                    else if(nums[l]+nums[r] < target)l++;
                    else {
                        ans.push_back({nums[i],nums[l],nums[r]});
                        l++;
                        r--;
                        while(l<r && nums[l]==nums[l-1])l++;
                        while(r>l && nums[r]==nums[r+1])r--;
                    }
                }
            }
            return ans;
        }
    };