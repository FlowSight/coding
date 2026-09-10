/// Severity: Sev0
// Date: 29Aug26
// LC: 910
// Where I failed: could not come up with split algo..made too complicated
// Pattern: greedy
// Notes: additional_notes



class Solution {
public:
    int smallestRangeII(vector<int>& a, int k) {
            sort(a.begin(), a.end());
            int n = a.size();
            int ans = a[n-1] - a[0];
            for (int i = 0; i < n-1; i++) {
                int hi = max(a[i] + k, a[n-1] - k);
                int lo = min(a[0] + k, a[i+1] - k);
                ans = min(ans, hi - lo);
            }
            return ans;
    }
};