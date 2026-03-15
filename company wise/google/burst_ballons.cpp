// Severity: Sev2
// Date: 15Mar26
// LC: 312
// Where I failed: dry run
// Pattern: dp



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        dp = vvi(n,vi(n,0));
        for(auto len=1;len<=n;len++){
            for(auto left=0;left+len-1<n;left++){
                int right = left+len-1;
                for(auto i=left;i<=right;i++){
                    auto cur = nums[i];
                    if(left-1>=0) cur *= nums[left-1];
                    if(right+1 < n) cur *= nums[right+1];
                    dp[left][right] = max(dp[left][right], 
                        cur + (left <=i-1 ? dp[left][i-1]:0)  
                        +(i+1 <= right ?  dp[i+1][right] : 0 ) );
                }
            }
        }
        return dp[0][n-1];
    }
    int helper(vi& nums,int l , int r, int& n){
        if(l>r) return 0;
        if(dp[l][r] != -1) return dp[l][r];
        int ans = 0,left = 1, right = 1;
        for(auto i=l;i<=r;i++){
            // i burst at last
            if(l-1>=0)left = nums[l-1];
            if(r+1<n)right = nums[r+1];
            ans = max(ans,nums[i]*left*right + helper(nums,l,i-1,n) + helper(nums,i+1,r,n));
        }
        return dp[l][r] = ans;
    }
};