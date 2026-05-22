/// Severity: Sev2
// Date: 18May26
// LC: 2009
// Where I failed: took time to think..sev1
// Pattern: sliding window
// Notes: took time to think



class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), l = 0, r = 0, cnt = 0, ans = n;
        sort(nums.begin(),nums.end());
        while(l<n){
            while((r<n) && (nums[l]+n-1 >= nums[r])) {
                if((r==l) || (nums[r] != nums[r-1])) cnt++;
                r++;
            }
            ans = min(ans,n-cnt);
            cnt--;
            l++;
            while((l<n) && (nums[l] == nums[l-1])) l++;
        }
        return ans;
    }
};

// 1 2 2 3 3 7 8
// l.        r limit = 7 cnt = 4 req = 7-4=3
//   l         r limit = 8 cnt = 4 req = 7-5=2
// 1 : 6