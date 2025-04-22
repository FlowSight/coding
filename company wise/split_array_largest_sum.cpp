// 11 apr 2025
// did dp..clean
// got the idea of bs while doing dp..did it clean 
// missed 2 corner cases 
// sev2

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        int splitArray(vector<int>& nums, int k) {
            int l = 0,r = 0,mid = 0;
            for(auto it : nums) r += it;
            while(l<r){
                if(l+1 == r){
                    return tryPartition(nums,k,l) ?  l : r;
                }
                mid = (l+r)/2;
                if(tryPartition(nums,k,mid)) {
                    r = mid;
                } else {
                    l = mid+1;
                }
            }
            return l;
        }
    
        bool tryPartition(vi& nums, int k, int target){
            int n = nums.size(), sum = 0;
            for(auto i=0;i<n;i++) {
                if(sum + nums[i] >target) {
                    k--;
                    if(k == 0) return false;
                    sum = 0;
                }
                sum += nums[i];
                if(sum > target) return false;
            }
            return sum <= target;
        }
    };

    class Solution {
        public:
            typedef vector<int> vi;
            typedef vector<vi> vvi;
        
            int splitArray(vector<int>& nums, int k) {
                int n = nums.size();
                vvi dp(n+1,vi(k+1,-1));
                for(auto i=0;i<=k;i++) dp[0][i] = 0;
                for(auto i=1;i<=n;i++)dp[i][1] = dp[i-1][1]+nums[i-1];
        
                for(auto i=1;i<=n;i++){
                    for(auto j=2;j<=k;j++){
                        dp[i][j] = INT_MAX;
                        for(auto x = i,sum = 0;x>=0;x--){
                            if(j>x) break;
                            sum+=nums[x-1];
                            dp[i][j] = min(dp[i][j],max(dp[x-1][j-1],sum));
                        }
                        if(dp[i][j] == INT_MAX) dp[i][j] = -1;
                    }
                }
                return dp[n][k];
            }
        };
        
        // n^2*k
        // dp[i][j] = till i making j partitions where ith element is the last element of jth partition
        // need output as max sum which is min