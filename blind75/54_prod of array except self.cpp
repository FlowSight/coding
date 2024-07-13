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