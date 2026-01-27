// 25jan2026.
// sev0.sev0.didnt get idea..

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs[0].size(), m = strs.size(), ans = 1;
        vector<int> dp(n,1);
        for(auto i=1;i<n;i++){
            for(auto j=i-1;j>=0;j--){
                if(greater(strs,i,j)) dp[i] = max(dp[i],dp[j]+1);
            }
             ans = max(ans,dp[i]);
        }
        return n-ans;
    }
    bool greater(vector<string>& arr,int idx1, int idx2){
        int n = arr.size();
        for(auto i=0;i<n;i++){
            if(arr[i][idx1] < arr[i][idx2]) return false;
        }
        return true;
    }
};