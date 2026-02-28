/// Severity: Sev1
// Date: 28Feb26
// LC:862
// Where I failed: getting to sol..dry run
// Pattern: monotone queue, pref sum




class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int  n = nums.size(), ans = n+1;
        vector<long> pref(n,0);
        deque<int> q;
        for(auto i=0;i<n;i++){
            pref[i] = (nums[i] +  (i? pref[i-1] : 0));
            if(pref[i] >=k) ans = min(ans,i+1);
            while(!q.empty() && (pref[i] - pref[q.front()] >=k)) {
                ans = min(ans,(i-q.front()));
                q.pop_front();
            }
            while(!q.empty() && (pref[i] <= pref[q.back()])) q.pop_back();
            q.push_back(i);
        }
        return ans == n+1 ? -1 : ans;
    }
};
