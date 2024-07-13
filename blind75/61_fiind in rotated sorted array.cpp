class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int idx = findPivot(nums);
        cout<<idx<<endl;
        if(idx == -1) return findInSortedArr(nums,0,n-1,target);
        return ((target <= nums[idx]) && (target >= nums[0])) ? findInSortedArr(nums,0,idx,target) : findInSortedArr(nums,idx+1,n-1,target);
    }

    int findInSortedArr(vector<int>& nums,int l, int r, int target){
        if(l<0 || r<0 || l>=nums.size() || r>=nums.size())return -1;
        int mid  = 0;
        while(l<r){
            if(l+1 == r)return nums[l] == target ? l : nums[r] == target ? r : -1;
            mid = (l+r)/2;
            if(nums[mid] == target)return mid;
            if(nums[mid] < target)l = mid+1;
            else r = mid-1;
        }
        return nums[l] == target ? l : -1;
    }

    int findPivot(vector<int>& nums){
        int l = 0, r = nums.size()-1, mid = 0;
        while(l<r){
            if(l+1 == r)return nums[l] > nums[r] ? l : -1;
            mid = (l+r)/2;
            if(nums[mid] > nums[l]) {
                // below 2 lines are unnecessary .. just r = mid is enough...could not prove why while writing this
                if(nums[mid] > nums[r]) l = mid;
                else r = mid;
            } else {
                r = mid;
            }
            // below 2 lines are unnecessary
            if(nums[mid] > nums[r]) r = mid+1;
            else l = mid+1;
        }
        return l;
    }
};

// the above was my first code...mistake was i overcomplicated the mid comparison..i compared it with left..instead if i just compared with right...w
why?
because..i tried to find the pivot..in my mind pivot was the element which was greater than left and right..but i should have just found the smallest..its much simpler..
but lets say..even if i wanted to find the largest..