// Severity: Sev2
// Date: 15Feb26
// 
// How much solved: Fully
// Where I failed: minor compile mistake
// Pattern: dp
// Notes: TODO: 1d dp


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int minimumDistance(string word) {
        int n = word.size(), ans = INT_MAX;
        vector<unordered_map<string,int>>  dp(n);
        for(auto i='A';i<='Z';i++) {
            dp[0][makeKey(word[0],i)] = 0;
            dp[0][makeKey(i,word[0])] = 0;
        }
        for(auto i=1;i<n;i++){
            for(auto it: dp[i-1]){
                auto c1 = it.first[0], c2 = it.first[2];
                auto key1 = makeKey(word[i],c2), key2 = makeKey(c1,word[i]);
                auto cost1 = it.second + getDist(c1,word[i]), cost2 = it.second + getDist(c2,word[i]);
                auto it1 = dp[i].find(key1);
                auto it2 = dp[i].find(key2);
                if(it1 == dp[i].end()) dp[i][key1] = cost1;
                else dp[i][key1] = min(dp[i][key1] , cost1);
                if(it2 == dp[i].end()) dp[i][key2] = cost2;
                else dp[i][key2] = min(dp[i][key2] , cost2);
                if(i==n-1) ans = min({ans,cost1,cost2});
            }
        }
        return ans;
    }
    int getDist(char& c1, char& c2){
        int d1 = (c1-'A'), d2 = (c2-'A'), r1 = d1/6, r2 = d2/6, col1 = d1%6, col2 = d2%6;
        return abs(r1-r2) + abs(col1-col2);
    }
    string makeKey(char c1, char c2){
        string ans(1,c1);
        ans.push_back('#');
        ans.push_back(c2);
        return ans;
    }
};

