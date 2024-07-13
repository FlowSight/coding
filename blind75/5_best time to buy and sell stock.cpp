class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, minSoFar = INT_MAX-2;
        for(auto it : prices){
            ans = max(ans,it-minSoFar);
            minSoFar = min(minSoFar,it);
        }
        return ans;
    }
};