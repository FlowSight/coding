class Solution {
public:
    int maxProfit(vector<int>& arr) {
        int n = arr.size(), ans = 0;
        for(auto i=1;i<n;i++){
            if(arr[i] > arr[i-1]) ans += arr[i]-arr[i-1];
        }
        return ans;
    }
};