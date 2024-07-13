class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            if(l+1 == r) {
                // fucked this up last time..in ming tried to find largest so did r--, 
                if(nums[l] > nums[r]) {
                    l++;
                }
                break;
            }
            int mid = (l+r)/2;
            if(nums[mid] == nums[r] && nums[mid] == nums[l])break;
            if(nums[mid] > nums[r]) l = mid+1;
            else r = mid;
        }
        if(l>=r) return target <= nums.back() ? searchInsortedArr(nums,l,nums.size()-1,target) : searchInsortedArr(nums,0,l-1,target);
        for(auto i=0;i<nums.size();i++)if(nums[i] == target)return true;
        return false;
    }

    // also fucked up here..thought that we need to return the index...
    bool searchInsortedArr(vector<int>& nums, int l, int r, int target) {
        if( l<0 || r<0 || l>=nums.size() || r>= nums.size())return false;
        while(l<r){
            int mid = (l+r)/2;
            if(nums[mid] == target)return true;
            if(nums[mid] > target) r = mid-1;
            else l = mid+1;
        }
        return nums[l] == target ? true : false;
    }
};

//learning : always write down the exact asks...