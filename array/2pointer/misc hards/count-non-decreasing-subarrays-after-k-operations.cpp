/// Severity: Sev0..sev0..sev0...sev0..Sev0..sev0..sev0...sev0..Sev0..sev0..sev0...sev0
// Date: 15Nov26
// LC: 3420
// Where I failed: 2 pointer inside 2 pointer
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        // q = {back....front}
        deque<int> q;
        long long ops = 0, ans = 0;
        int n = nums.size();
        for(int l=n-1,r=n-1;l>=0;l--){
            int hei = nums[l];
            
            while(!q.empty() && (nums[q.back()] <= hei)) {
                auto ll = q.back();// left most plateau's (l...r) l. hence r = next elem on left after popping (-1)
                q.pop_back();
                auto rr = (q.empty() ? r+1 : q.back()); // my bug was here (r+1, i did n). the range is current equal level plateau
                ops += 1LL * (rr-ll) * (hei-nums[ll]);
            }
            
            q.push_back(l);
            while(ops > k){
                ops -= 1LL * (nums[q.front()] - nums[r]);
                if(q.front() == r) q.pop_front();
                r--;
            }
            
            ans += (r-l+1);
        }
        return ans;
    }
};

