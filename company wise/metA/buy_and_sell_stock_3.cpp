// 21 may 2025
// saw a hint..sev0

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int firstBuy = -prices[0], firstSell = 0, secondBuy = INT_MIN, secondSell = 0,
            n = prices.size();
        for(auto i=1;i<n;i++){
            secondSell = max(secondSell, secondBuy + prices[i]);
            secondBuy = max(secondBuy,-prices[i]+firstSell);            
            firstSell = max(firstSell, firstBuy + prices[i]);
            firstBuy = max(firstBuy,-prices[i]);
        }
        return max(secondSell, firstSell);
    }
};