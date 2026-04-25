
// LC : 639

// 16apr2026
//sev0: didnt get the basic brute force + dp;

class Solution {
public:
    unordered_map<string,int> dp;
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return helper(price,special,needs,0);
    }
    int helper(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, int idx){
        int ans = getNormal(price,needs), n = needs.size(), sz = special.size();
        auto key = makekey(needs);
        if(dp.find(key) != dp.end()) return dp[key];
        for(auto i=idx;i<sz;i++){
            if(special[i].back() > ans) continue;
            vector<int> tmp;
            for(auto j=0;j<n;j++){
                if(special[i][j] > needs[j]) {
                    tmp.clear();
                    break;
                }
                tmp.push_back(needs[j] - special[i][j]);
            }
            if(tmp.size()) {
                ans = min(ans,special[i].back() + helper(price,special,tmp,idx));
            }
        }
        return dp[key] = ans;

    }
    string makekey(vector<int> arr){
        string ans = "$";
        for(auto it : arr){
            ans += to_string(it);
            ans.push_back('$');
        }
        return ans;
    }

    int getNormal(vector<int>& price,vector<int>& needs){
        int n = needs.size(), ans = 0;
        for(auto i=0;i<n;i++){
            ans += needs[i] * price[i];
        }
        return ans;
    }
};
