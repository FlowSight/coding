// 15 apr 2025.
// 12.30 mins..clean

//26jan 2025
// 9.30 mins..
// verdict : PASS
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r){
                if(nums[l]>nums[r]) return nums[r];
                return nums[l];
            }
            mid = (l+r)/2;
            if(nums[mid] < nums[l]) r = mid;
            else {
                if(nums[mid] < nums[r]) r = mid;
                else l = mid+1;
            }
        }
        return nums[l];
    }
};


class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r)return nums[l] <= nums[r] ? nums[l] : nums[r];
            mid = (l+r)/2;
            if((nums[l] > nums[mid]) || (nums[mid] <= nums[r])) r = mid;
            else l = mid+1;
        }
        return nums[l];
    }
};
