// 7 jan 2025
// 4.15 mins
// verdict : PASS

    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0,one = 0, zero = 0;
        for(auto r=0,l=0;r<n;r++){
            if(nums[r]) one++;
            else zero++;

            while((zero>k) && (l<=r)){
                if(nums[l])one--;
                else zero--;
                l++;
            }

            if(zero<=k) ans = max(ans,r-l+1);
        }
        return ans;
    }

