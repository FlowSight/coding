// 20 jan 2025
// 15 min..
// 1 compiler error.didnt cross check..
// verdict : FAIL

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size(), l = 0, r = n-1, mid = 0, left = 0, right = 0;
        while(l<r){
            if(l+1 == r){
                if(isPeak(nums,l))return l;
                return r;
            }
            mid = (l+r)/2;
            if(isPeak(nums,mid)) return mid;
            left = (mid == 0?INT_MIN : nums[mid-1]);
            right = (mid == nums.size()-1 ?INT_MIN : nums[mid+1]);

            if((left<=nums[mid]) && (nums[mid]<=right)) l = mid+1;
            else if((left>=nums[mid]) && (nums[mid]>=right)) r = mid-1;
            else {
                if(right>left) l = mid+1;
                else r = mid-1;
            }
        }
        return l;
    }

    bool isPeak(vector<int>& nums, int idx) {
        int left = (idx == 0?INT_MIN : nums[idx-1]),
            right = (idx == nums.size()-1 ?INT_MIN : nums[idx+1]);
        return (nums[idx]>left) && (nums[idx]>right);
    }

};

// >, not >=
// not unique