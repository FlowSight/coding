class Solution {
public:
    string getPermutation(int n, int k) {
        int i = 1, fact = 1;
        vector<int> nums;
        for(auto j=1;j<=n;j++){
            nums.push_back(j);
        }

        for(i=1;(fact*i < k);i++){
            fact *= i;
        }
        k-=fact;
        reverse(nums.begin()+n-i+1,nums.end());

        while(k--){
            nextPermutation(nums);
        }

        string ans = "";
        for(auto it : nums)ans.push_back(it+'0');
        return ans;
    }

    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), idx = n-1;
        for(;idx;idx--){
            if(nums[idx] > nums[idx-1]) break;
        }
        if(idx == 0){
            reverse(nums.begin(),nums.end());
            return;
        }
        int swapIdx = n-1;
        for(auto i=n-1;i>=idx;i--) {
            if(nums[i]>nums[idx-1]) {
                swapIdx = i;
                break;
            }
        }
        swap(nums[idx-1],nums[swapIdx]);
        reverse(nums.begin()+idx,nums.end());
    }
};
