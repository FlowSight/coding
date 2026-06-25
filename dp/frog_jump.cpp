/// Severity: Sev0..Sev0.. Sev0..Sev0..Sev0..Sev0.. Sev0..Sev0
// Date: 06Jun26
// LC: 403
// Where I failed: best implementation
// Pattern: dp
// Notes: key finding
// the point is, 
//  at any i, max jump can be i+1 (0 based index)



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        vvi dp(n,vi(n+1,0));
        dp[0][1] = 1;
        for(auto i=1;i<n;i++){
            for(auto j=0;j<i;j++){
                int diff = stones[i]-stones[j];
                if((diff <0) || (diff >n)  || !dp[j][diff]) continue;
                if(i==n-1) return true;
                dp[i][diff] = 1;
                if(diff-1 >=0) dp[i][diff-1] = 1;
                if(diff+1<=n) dp[i][diff+1] = 1;
            }
        }
        return false;
    }
};





