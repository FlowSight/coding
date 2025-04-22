// 13 apr 2025
// 5 mins..no error


// 26 dec 2024...6 mins..
// 1 compiler error
// 1 logic errr : didnt read qs: had to return vals insteadof index
// 1 logical error : corner case..boundary condition..
// verdict : FAIL


    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>>  ans;
        int n = nums.size();
        for(auto i=0;i<n;i++){
            while(i && (i<n) && (nums[i] == nums[i-1]))i++;
            if(i==n)continue;
            int l = i+1, r = n-1, target = -nums[i];
            while(l<r){
                if(nums[l]+nums[r] == target) {
                    ans.push_back({nums[i],nums[l],nums[r]});
                    l++;
                    r--;
                    while((l<r) && (nums[l] == nums[l-1])) l++;
                    while((l<r) && (nums[r] == nums[r+1])) r--;
                }
                else if(nums[l]+nums[r] < target) l++;
                else r--;
            }
        }
        return ans;
    }




// 7 nov 2024...i fucking lost it..could not even do the set approach...the other non-set approach didnt come to mind..somehow i was thinking about O(n) solution for 2sum and 
//  coupling one more loop for n^2..which was correct..but could not get that its gonna be sorted first..i thought it needs index wise unique, not value wise unique.
//  so i was going set path...didnt get the qs again..

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