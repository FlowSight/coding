// 8 may 2025
// didnt dry run..hence messed up..
// sev1

// 7 feb  2025
// came up with it myself..
// 15 mins..
// did dry run
// 1 compiler error..
// verdict : FAIL
// severity : sev3

    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), idx = n-1;
        for(;idx;idx--){
            if(nums[idx] > nums[idx-1]) break;
        }
        if(idx == 0){
            reverse(nums.begin(),nums.end());
            return;
        }
        int swapIdx = n-1;
        for(auto i=n-1;i>=idx;i--) {
            if(nums[i]>nums[idx-1]) {
                swapIdx = i;
                break;
            }
        }
        swap(nums[idx-1],nums[swapIdx]);
        reverse(nums.begin()+idx,nums.end());
    }

// severity : sev0

class Solution {
public:
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
    	int n = nums.size(), k, l;
    	for (k = n - 2; k >= 0; k--) {
            if (nums[k] < nums[k + 1]) {
                break;
            }
        }
    	if (k < 0) {
    	    reverse(nums.begin(), nums.end());
    	} else {
    	    for (l = n - 1; l > k; l--) {
                if (nums[l] > nums[k]) {
                    break;
                }
            } 
    	    swap(nums[k], nums[l]);
    	    reverse(nums.begin() + k + 1, nums.end());
        }
    }
}; 
};