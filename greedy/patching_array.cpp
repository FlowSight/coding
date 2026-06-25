/// Severity: Sev0..sev0..Sev0..sev0..Sev0..sev0..
// Date: 05Jun26
// LC: 330.
// Where I failed: algo..completely failed
// Pattern: pattern_name
// Notes: additional_notes



class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long long miss = 1, idx =0, ans = 0;
        for(;miss<=n;){
            if((idx<nums.size()) && (nums[idx] <= miss)) miss += nums[idx++];
            else miss<<=1, ans++;
        }
        return ans;
    }
};