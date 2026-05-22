class BIT {
    public:
    vector<int> arr;
    int n;
    BIT(int _n){
        n = _n;
        arr = vector<int>(n+1,0);
    }
    void add(int idx,int val){
        idx++;
        while(idx <= n) {
            arr[idx]+=val;
            idx += (idx & (-idx));
        }
    }
    int  prefsum(int idx){
        idx++;
        int ans = 0;
        while(idx > 0) {
            ans += arr[idx];
            idx -= (idx & (-idx));
        }
        return ans;
    }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> arr(n,0);
        unordered_map<int,int> idxs;
        BIT bit(n);
        long long ans = 0;
        for(auto i=0;i<n;i++){
            idxs[nums2[i]] = i;
        }
        // for each i, check how many smaller on left, how many greater on right;
         for(auto i=0;i<n;i++){
            if(i && (i<n-1)){
                long long idx = idxs[nums1[i]], smaller = bit.prefsum(idx), leftgreater = i-smaller,totalgreater = n-1-idx,
                    greater = totalgreater-leftgreater;
                ans += (smaller * greater);
            }
            bit.add(idxs[nums1[i]],1);
         }
         return ans;
    }
};
