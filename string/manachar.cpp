// check palindrome in O(n)

// left...x..center...i..right
// left....i..center....right...not possible

// so dp[x] should be same as dp[i] only when x+dp[x]<center and x-dp[x]>=left 
// this means i+dp[x]<=right
// if i+dp[x]>right then dp[i] = right - i // this is the crunch

cclass Solution {
public:
    typedef vector<int> vi;
    string longestPalindrome(string s) {
        if(s.size() <=1) return s;
        string str = "#", ans = "";
        for(auto c : s){
            str.push_back(c);
            str.push_back('#');
        }
        int n = str.size(), right = 0, center = 0, ansL = 1, maxLen = 1;
        vi dp(n,0);
        for(auto i=0;i<n;i++){
            if(right>=i) dp[i] = min(right-i,dp[2*center-i]);
            
            while((i-dp[i]-1 >=0) && (i+dp[1]+1<n) && str[i-dp[i]-1] == str[i+dp[i]+1])dp[i]++;

            if(dp[i]+i>right){
                right = dp[i]+i;
                center = i;
            }
            if(maxLen < 2*dp[i]+1){
                maxLen = 2*dp[i]+1;
                ansL = i-dp[i];
            }
        }
        for(auto i=ansL;i<ansL+maxLen;i++){
            if(str[i] == '#')continue;
            ans.push_back(str[i]);
        }
        return ans;
    }
};
