/// Severity: Sev0..sev0..sev0..
// Date: 21May26
// LC: 1696
// Where I failed: algo
// Pattern: pattern_name
// Notes: i thought, from i ...i+k-1..picking max will suffice.. it wont
//  we nee dp[i] = max score till now which means picking max dp[j] where j>=i-k and j<i 



class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        deque<int> q;
        q.push_back(0);
        int n = nums.size();
        vector<int> dp(n,0);
        dp[0] =  nums[0];
        for(auto i=1;i<n;i++){
            if(i-q.front() > k) q.pop_front();
            dp[i] = nums[i] + dp[q.front()]; 
            while(!q.empty() && (dp[i] >= dp[q.back()])) q.pop_back(); 
            q.push_back(i);
        }
        return dp[n-1];
    }
};