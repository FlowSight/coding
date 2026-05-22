/// Severity: Sev0
// Date: 18May26
// LC: 995
// Where I failed: algo
// Pattern: pattern_name
// Notes: sev0..sev0..sev0..


class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size(), flip = 0, ans = 0;
        deque<int>  flipped;
        for(auto i=0;i<n;i++){
            if(i>=k) {
                flip ^= flipped.back();
                flipped.pop_back();
            }
            if(flip == nums[i]){
                flipped.push_front(1);
                flip ^= 1;
                ans++;
                if(i+k-1 >=n) return -1;
            } else {
                flipped.push_front(0);
            }
        }
        return ans;
    }
};