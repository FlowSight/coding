// 15 apr 2025..
// could not match finally..forgot algo
// sev0

// 12 feb 2025..
// could not match finally..forgot algo
// sev0


//27 oct 2024
// sev1

class Solution {
public:

    // below are O(log(min(m,n))) solution
    // we are maintaining left,right for arr1, and based on that we will pick point in arr2
    double helper(vi& arr1, vi& arr2, int k, int& left, int& right){
        if(left>right)return 0;

        // this is basically calculating how much cut are we discarding from arr1 and arr2. the element before cut and at the cut are our concern
        int cut1 = (left+right)/2, cut2 = k-cut1;
        int l1 = (cut1==0?INT_MIN:arr1[cut1-1]), r1 = (cut1==arr1.size()?INT_MAX:arr1[cut1]),
            l2 = (cut2==0?INT_MIN:arr2[cut2-1]), r2 = (cut2==arr2.size()?INT_MAX:arr2[cut2]);
        // this is to basically guarantee that the order is, (l1,l2), (r1,r2)
        // if this is the case then, its intersecting..that means..some 2 nos out of these 4 wiill give median
        // internalize this below code : imagine you have cut1 in arr1 and cut2 in arr2.you must pick the larger one,
        //(1,3), (2,4) => l1=1,r1 = 3, l2 = 2, r2 = 4 => max(1,2) = 2, min(3,4) = 3 => median = (2+3)/2...
        // (2,3), (1,5) => l1=2,r1 = 3, l2 = 1, r2 = 5 => max(2,1) = 2, min(3,5) = 3 => median = (2+3)/2...
        if((l1<=r2 )&& l2<=r1){ 
            return (arr1.size()+arr2.size())%2 ? max(l1,l2) : (double)(max(l1,l2)+min(r1,r2))/2.0;
        }
        // this is when the actual median is probably much left in arr1..
        if(l1>r2) right = cut1-1;
         // this is when the actual median is probably much right in arr1..
        else left = cut1+1;
        return helper(arr1,arr2,k,left,right);
    }

    // below are O(log(k)) solution
    // iterative
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size(), idx1 = 0, idx2 = 0, k = (n1+n2+1)/2;

        while(k){
            if(idx1 >= n1){
                idx2 = idx2+k-1;
                return (double)(nums2[idx2]+ ((n1+n2)%2 ? nums2[idx2] : nums2[idx2+1]))/(double)2.0;
            }
            if(idx2 >= n2) {
                idx1 = idx1+k-1;
                return (double)(nums1[idx1]+ ((n1+n2)%2 ? nums1[idx1] : nums1[idx1+1]))/(double)2.0;
            }
            if(k==1) {
                double odd, even;
                if(nums1[idx1] <= nums2[idx2]){
                    odd = nums1[idx1];
                    even = ((n1+n2)%2 ? nums1[idx1] : min((idx1+1 < n1 ? nums1[idx1+1] : INT_MAX),nums2[idx2]));
                } else {
                    odd = nums2[idx2];
                    even = ((n1+n2)%2 ? nums2[idx2] : min((idx2+1 < n2 ? nums2[idx2+1] : INT_MAX),nums1[idx1]));
                }
                return (double)(odd+even)/(double)2.0;
            } 
            auto newIdx1 = (idx1+k/2-1 < n1 ? idx1+k/2-1 : n1-1), newIdx2 = (idx2+k/2-1 < n2 ? idx2+k/2-1 : n2-1);
            if(nums1[newIdx1] < nums2[newIdx2]){
                k -= (newIdx1-idx1+1);
                idx1 = newIdx1+1;
            } else {
                k -= (newIdx2-idx2+1);
                idx2 = newIdx2+1;
            }
        }
        return 1;
    }
    // recursive
    double findMedianOfSortedArraysHelper(vector<int>& nums1, vector<int>& nums2, int idx1, int idx2, int k, int n1, int n2) {
        if(idx1 >= n1)return nums2[idx2+k-1];
        if(idx2 >= n2)return nums1[idx1+k-1];
        if(k==1) return nums1[idx1] < nums2[idx2] ? nums1[idx1] : nums2[idx2];
        auto newIdx1 = (idx1+k/2-1 < n1 ? idx1+k/2-1 : n1-1), newIdx2 = (idx2+k/2-1 < n2 ? idx2+k/2-1 : n2-1);
        if(nums1[newIdx1] < nums2[newIdx2]){
            return findMedianOfSortedArraysHelper(nums1,nums2,newIdx1+1,idx2,k-(newIdx1-idx1+1),n1,n2);
        } else {
            return findMedianOfSortedArraysHelper(nums1,nums2,idx1,newIdx2+1,k-(newIdx2-idx2+1),n1,n2);
        }
    }
};

// forgot the idea
// took looooong time to code even after seeing
// made mistake in indexing
// madem mistake in corner cases