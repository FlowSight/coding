// 31 jan26, could think of n^2d sol..could not tink  of O(nd) sol 
// sev0..sev0..

class Solution {
public:
    int minDifficulty(vector<int>& arr, int day) {
        int n = arr.size();
        if(day>n) return -1;
        vector<int> dp(n,1e7), dp2(n,1e7), st;
        for(auto d=0;d<day;d++){
            st.clear();
            for(auto i=d;i<n;i++){
                dp2[i] = arr[i] + (i?dp[i-1]:0);
                while(!st.empty() && (arr[st.back()] <= arr[i])) {
                    auto tp = st.back();
                    st.pop_back();
                    dp2[i] = min(dp2[i],dp2[tp] - arr[tp] + arr[i]);
                }
                if(!st.empty()) {
                    dp2[i] = min(dp2[i],dp2[st.back()]);
                }
                st.push_back(i);
            }
            dp = dp2;
        }
        return dp.back();
    }
};
