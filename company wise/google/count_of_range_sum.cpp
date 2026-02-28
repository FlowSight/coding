/// Severity: Sev0
// Date: 28Feb26
// LC: 327
// Where I failed: algo and corner case
// Pattern: merge sort and segment tree



class Solution {
public:
    typedef vector<long> vl;
    typedef vector<vl> vvl;
    int ans;
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        ans = 0;
        long pref = 0;
        vvl arr;
        arr.push_back({0,-1});
        for(auto i=0;i<n;i++) {
            pref+=nums[i];
            arr.push_back({pref,i});
        }
        helper(arr,lower,upper,0,n);
        return ans;
    }

    void helper(vvl& arr, int& lower, int& upper, int left, int& right){
        if(left >= right) return;
        int mid = (left+right)/2, ll = right, rr = ll;
        helper(arr,lower,upper,left,mid);
        helper(arr,lower,upper,mid+1,right);
        for(auto i=mid;(i>=left);i--){
            while((rr>=mid+1) && (arr[rr][0] - arr[i][0] > upper))rr--;
            ll = rr;
            while((ll>=mid+1) && (arr[ll][0] - arr[i][0] >= lower))ll--;
            ll++;
            ans += (rr-ll+1);
        }
        inplace_merge(arr.begin()+left,arr.begin()+mid+1,arr.begin()+right+1);
    }
};

// 0 -1 0


//  1 3 6    5 7
//  1 2 3 -1 2
//  [2,4]