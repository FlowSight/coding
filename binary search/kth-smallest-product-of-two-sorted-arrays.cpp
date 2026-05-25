/// Severity: Sev0..sev0
// Date: 23May26
// LC: 2040
// Where I failed: implement
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    typedef long long ll;
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        int m = nums1.size(), n = nums2.size();
        long long l = -1e10, r  = 1e10;
        while(l<r){
            if(l+1 == r) {
                auto cnt = getlesseq(nums1,nums2,l);
                return cnt >= k ? l : r;
            }
            long long mid = (l+r)/2;
            auto cnt = getlesseq(nums1,nums2,mid);
            if(cnt >= k) r = mid;
            else l = mid+1;
        }
        return l;
    }

    long long getlesseq(vector<int>& nums1, vector<int>& nums2, long long num){
        long long ans = 0;
        for(auto it : nums2){
            if(it == 0){
                if(num >= 0) ans += nums1.size();
                continue;
            }
            int n = nums1.size(), lo = 0, hi = n;
            if(it > 0){
                while(lo < hi){
                    int mid = (lo + hi) / 2;
                    if((ll)nums1[mid] * it <= num) lo = mid + 1;
                    else hi = mid;
                }
                ans += lo;
            } else {
                while(lo < hi){
                    int mid = (lo + hi) / 2;
                    if((ll)nums1[mid] * it <= num) hi = mid;
                    else lo = mid + 1;
                }
                ans += n - lo;
            }
        }
        return ans;
    }
};
