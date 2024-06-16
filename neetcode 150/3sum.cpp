class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size();
        vector<vector<int>>  ans;
        for(auto i=0;i<n;i++){
            if( i && (nums[i] == nums[i-1])) continue;
            int rem = -nums[i];
            int l = i+1, r = n-1;
            while(l<r){
                if(nums[l] + nums[r] < rem){
                    l++;
                    while((l<r) && nums[l]==nums[l-1])l++;
                }
                else if(nums[l] + nums[r] > rem){
                    r--;
                    while((l<r) && nums[r]==nums[r+1])r--;
                }
                else {
                    ans.push_back({nums[i],nums[l],nums[r]});
                    l++;
                    while((l<r) && nums[l]==nums[l-1])l++;
                    r--;
                    while((l<r) && nums[r]==nums[r+1])r--;
                }
            }
        }
        return ans;
    }
};