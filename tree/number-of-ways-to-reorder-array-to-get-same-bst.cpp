/// Severity: Sev0
// Date: 21Jun26
// LC: 1569
// Where I failed: took 2 days..but came up with it on my own
// Pattern: pattern_name
// Notes: additional_notes


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int mod = 1e9+7;
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        dp = vvi(n+1,vi(n+1,0));
        for(auto i=1;i<=n;i++) {
            dp[0][i] = dp[i][0] = 1;
        }
        for(auto i=1;i<=n;i++){
            for(auto j=1;j<=n;j++){
                dp[i][j] = (dp[i-1][j] + dp[i][j-1])%mod;
            }
        }
        return helper(nums) - 1;
    }

    // return no of ways to get tree formed by nums
    long helper(vi& nums){
        int n = nums.size();
        if(n<=2) return 1;
        vi left, right;
        for(auto i=1;i<n;i++) {
            if(nums[i] <nums[0]) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }
        long ll = helper(left) ,  rr = helper(right),
            lsz = left.size(), rsz = right.size();
        return ((dp[lsz][rsz] * ll )%mod * rr) %mod;
    }

}; 



// [3,4,5,1,2]
// why not [3,4,5,1,2] is a ans?