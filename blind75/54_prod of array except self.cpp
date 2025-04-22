// 12 apr 2025
// 7 miins..
// no mistake..
// // verdict : PASS

// 2 jan 2025
// 7.30 mins..
// no mistake
// vedict : PASS

//  18 dec 2024..5 mins..only mistake was i took mod even though the numbers could have beem negative
//  Verdict : PASS
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(),cur = 1,mod = 1e9+7;
        vector<int> ans(n,0);
        for(auto i=n-1;i>=0;i--){
             ans[i] = (i==n-1)?nums[i]:(ans[i+1]*nums[i]);
        }
        for(auto i=0;i<n;i++){
            int lMult = cur, rMult = (i==n-1)?1:ans[i+1];
            ans[i] = (lMult*rMult);
            cur = (cur*nums[i]);
        }
        return ans;
    }




class Solution {
public:
    typedef vector<int> vi;
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(), cur = 1;
        vi ans(n,0);
        ans[0] = nums[0];
        for(auto i=1;i<n;i++){
            ans[i] = ans[i-1]*nums[i];
        }
        for(auto i=n-1;i>0;i--){
            ans[i] = cur*ans[i-1];
            cur = cur*nums[i];
        }
        ans[0] = cur;
        return ans;
    }
};