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

class Solution {
public:
    int maxProfit(vector<int>& arr) {
        int n = arr.size(), buyMax = -arr[0], sellMax = 0;
        for(auto i=1;i<n;i++){
            auto sell = buyMax + arr[i],
                buy = sellMax - arr[i];
            buyMax = max(buyMax,buy);
            sellMax = max(sellMax,sell);
        }
        return sellMax;
    }
};