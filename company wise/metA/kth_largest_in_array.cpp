// 14 june 2025
// my main problem is i overlook the k-1 index and >=/< v/s >/<= logic 

// 30 apr 2025
// got the >=...< idea but wronged the parittion caller binary search logic..resulted into timeuut.
// sev0

// 13 apr 2025
// forgot partition algo..
// also didnt quite think through the left and right boundary selection after
// partitioning.
// sev0
// still dont exactly know the Tc calculations..
// most resources say : T(n) = T(n/2) + O(n) = O(n) ...because every time
// we randomly choose a pivot, we almost partition it into half..but its not complete proof 
// also need to discuss range of no (counting sort)


// this qs has 2 hard variant in meta : implement heap, do quickselect
class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) {
            int l = 0, n = nums.size(), r = n-1, idx = 0;
            while(true) {
                idx = partition(nums,l,r);
                if(idx == k-1) return nums[idx];
                if(idx > k-1) r = idx-1;
                else l = idx+1;
            }
            return -1;
        }
        int partition(vector<int>& nums, int l, int r) {
    
            int idx = rand()%(r-l+1) + l;
            swap(nums[l],nums[idx]);
            for(auto i=l+1;i<=r;i++){
                if(nums[i] < nums[l]){
                    swap(nums[r--],nums[i--]);
                } 
                if((r>i) && (nums[r]<=nums[l]))r--;
            }
            swap(nums[l],nums[r]);
            return r;
        }
    };