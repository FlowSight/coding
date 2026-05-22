/// Severity: Sev0
// Date: 20May26
// LC: 321
// Where I failed: could not think...brute force is best..only approach..
// Pattern: brute force, unsorted array merge 
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size() , n = nums2.size();
        vi ans(k,0);
        for(auto i=0;i<=k;i++){ // O(k)
            if(i>m || (k-i>n)) continue;
            auto arr1 = getmaxarr(nums1,i), arr2 =  getmaxarr(nums2,k-i); //O(m+n)
            auto arr = merge(arr1,arr2); // O(m+n)^2
            if(arr > ans) ans = arr;
        }
        return ans; // O(m+n)^3
    }
    vi merge(vi& arr1, vi& arr2){
        vi ans;
        int idx1 = 0, idx2 = 0;
        while((idx1 < arr1.size()) && (idx2 < arr2.size())){
            if(greater(arr1,idx1,arr2,idx2)) ans.push_back(arr1[idx1++]);
            else ans.push_back(arr2[idx2++]);
        }
        while((idx1 < arr1.size()) )ans.push_back(arr1[idx1++]);
        while(idx2 < arr2.size())ans.push_back(arr2[idx2++]);
        return ans;
    }
    bool greater(vi& arr1, int idx1, vi& arr2, int idx2){
        int m = arr1.size(), n = arr2.size();
        while((idx1<m) && (idx2<n) && (arr1[idx1] == arr2[idx2])) {
            idx1++;
            idx2++;
        }
        if(idx1 == m) return false;
        if(idx2 == n) return true;
        return arr1[idx1] > arr2[idx2];
    }

    vi getmaxarr(vi& nums, int k){
        if(k==0) return {};
        int n = nums.size();
        if(k==n) return nums;
        
        vi ans(k,0);
        for(auto i=0,j=0;i<n;i++){
            // imp condition : ans[j-1] <= nums[i] is wrong, same val might produce higher number
            while(j && (ans[j-1] < nums[i]) && (n-i+j >= (k+1))) {
                j--;
            }
            if(j<k){
                ans[j++] = nums[i];
            }
        }
        return ans;
    }


};

