// 17 may 2025..took a lot of tume to think

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
            int left = (mid == 0? INT_MIN : nums[mid-1]),
                right = (mid == n-1? INT_MIN : nums[mid+1]);
            if(nums[mid] < nums[r]) l = mid+1;
            else if(nums[mid] < nums[l]) r = mid-1;
            else {
                if(left > right) r = mid-1;
                else l = mid+1;
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

// Key:
// >, not >=
// not unique, but nums[i] != nums[i+1]
// if end is higher than current, then ans MUST be in that half
// if both ends are smaller, lean toward the half which has immediate larger element
// key is last element, if thats higher, its provable that ans is in that half