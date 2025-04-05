// 16 feb 
// 2 min n^2
// 10 mins nlogn
// verdict : PASS

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 1;
        vector<int> dp = {nums[0]};
        for(auto i=1;i<n;i++){
            int idx = findPos(dp,nums[i]);
            if(idx == -1) dp.push_back(nums[i]);
            else dp[idx] = nums[i];
        }
        return dp.size();
    }

    int findPos(vector<int>& arr, int num){
        int n = arr.size(), l = 0, r = n-1, mid = 0;
        while(l<r){
            if(l+1 == r){
                if(arr[l] >= num) return l;
                return arr[r] >= num ? r :  -1;
            }
            mid = (l+r)/2;
            if(arr[mid] == num) return mid;
            if(arr[mid] > num) r = mid;
            else l = mid;
         }
         return arr[l] >= num ? l :  -1;
    }
};




class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 1;
        vector<int> dp = {nums[0]};

        for(auto i=1;i<n;i++){
            int ub = upper_bound(dp,nums[i]);
            if(ub == -1){
                dp.push_back(nums[i]);
            } else {
                dp[ub] = nums[i];
            }
        }
        return dp.size();
    }

    int upper_bound(vector<int>& dp, int num){
        int l = 0, r = dp.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r)return dp[l]>=num ? l : dp[r] >= num ? r : -1;
            mid = (l+r)/2;
            if(dp[mid] == num)return mid;
            if(dp[mid] > num)r = mid;
            else l = mid+1;
        }
        return dp[l] >= num ? l : -1;
    }
};