class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int pivotIdx = findPivot(nums,0,n-1);
        if(pivotIdx == -1) return find(nums,0,n-1,target);
        if(nums[0]<=target) return find(nums,0,pivotIdx,target);
        return find(nums,pivotIdx+1, n-1,target);
    }


    int findPivot(vector<int>& nums, int l, int r){
        int n = nums.size(),  mid = 0;
        while(l<r){
            if(l+1 == r){
                if(nums[l]>nums[r]) return l;
                if( (r<n-1) && (nums[r] > nums[r+1])) return r;
                return -1;
            }
            mid = (l+r)/2;
            if(nums[l] > nums[mid]) r = mid;
            else if(nums[mid] > nums[r]){
                l = mid;
            } else if(nums[l] < nums[mid]){
                l = mid;
            } else if(nums[mid] < nums[r]){
                r = mid;
            } else {
                auto ll = findPivot(nums,l,mid);
                if(ll != -1) return ll;
                return findPivot(nums,mid+1,r);
            }
        }
        return  ((l<n-1) && (nums[l] > nums[l+1])) ? l : -1;
    }

    bool find(vector<int>& nums, int l,int r, int target){
        int mid =0 ;
        while(l<r){
            mid = (l+r)/2;
            if(nums[mid] == target) return true;
            if(nums[mid] < target) l = mid+1;
            else r = mid-1;
        }
        return nums[l] == target;
    }
};



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