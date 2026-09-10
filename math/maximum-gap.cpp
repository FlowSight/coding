/// Severity: Sev0
// Date: 04Sep26
// LC: 164
// Where I failed: algo, why gap=(max-min)/(n-1)
// Pattern: bucket sort
// Notes: min(max gap ) = (max-min)/(n-1), make n-1 buckets of size min(maxgap)
// within bucket maximum (wbm) : gap = min(maxgap)-1, 
//across bucket maximum (abm) : min of next bucket - min of prev bucket
/* why abm < wbm cant hold true? because wbm is upper-bounded by bucketSize ≤ average gap,
                          and the TRUE max gap ≥ average gap (pigeonhole) — so whatever
                          achieves the true max gap CANNOT be a within-bucket pair;
                          it MUST be an across-bucket pair (or exactly equal to bucketSize
                          in a degenerate all-equal-spacing case, but even then the
                          across-bucket check still finds a value tied with it)*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n<2) return 0;
        int gap = 0, minnum = INT_MAX, maxnum = INT_MIN, ans = INT_MIN;
        for(auto it : nums){
            minnum = min(minnum,it);
            maxnum = max(maxnum,it);
        }
        gap = (maxnum-minnum)/(n-1) + ((maxnum-minnum)%(n-1) != 0);
        vector<int> bmin(n-1,INT_MAX), bmax(n-1,INT_MIN);
        for(auto it : nums){
            if(it == maxnum) continue;
            int idx = (it-minnum)/gap;
            bmin[idx] = min(bmin[idx],it);
            bmax[idx] = max(bmax[idx],it);
        }
        int last = minnum;
        for(auto i=0;i<n-1;i++){
            if(bmin[i] == INT_MAX) continue;
            ans = max(ans,bmin[i]-last);
            last = bmax[i];
        }
        return max(ans,maxnum-last);
    }
};
