//30/12/25..was able to run in one shot

class Solution {
public:
    string shortestPalindrome(string s) {
        int prefLen = manachar(s), n = s.size();
        string ans = "";
        for(auto i=n-1;i>=prefLen;i--){
            ans.push_back(s[i]);
        }
        for(auto c: s)ans.push_back(c);
        return ans;
    }
    int manachar(string& s){
        string str = "#";
        for(auto c:s){
            str.push_back(c);
            str.push_back('#');
        }
        int n = str.size(), center =0, right = 0, maxLen = 0;
        vector<int> dp(n,0);
        for(auto i=0;i<n;i++){
            if(2*center>=i) {
                int left = 2*center-i;
                dp[i] = min(right-i,dp[left]);
            }
            while((i-dp[i]-1>=0) && (i+dp[i]+1 <n) && (str[i-dp[i]-1] == str[i+dp[i]+1])) dp[i]++;
            if(dp[i]+i > right){
                right = dp[i]+i;
                center = i;
            }
            if(i-dp[i] == 0) {
                if(str[i] == '#') maxLen = max(maxLen,dp[i]);
                else maxLen = max(maxLen,1+(dp[i]/2)*2);
            }
        }
        return maxLen;
    }
};

// #b#a#a#b#
// b # a # f # a # b
// 1:1
// 2:3
// 3:3
// 4


// .l..center..i..right
// center-i-center
// only a-z?yes
// len = 5e4

// aacecaa a
// dcbabcd