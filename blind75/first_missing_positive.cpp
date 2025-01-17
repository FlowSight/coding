// 6 nov 2024.
// missed ONE bloody stupid mistake in code...didn dry run fully...was feeling restless..6 mins
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(auto i=0;i<n;i++){
            while(nums[i]<=n && nums[i]>0 && (nums[i] != i+1) && nums[nums[i]-1]!=nums[i] ){
                swap(nums[i],nums[nums[i]-1]);
            }
        }
        for(auto i=0;i<n;i++){
            if(nums[i] != i+1)return i+1;
        }
        return n+1;
    }
};