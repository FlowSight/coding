// 30/12/25..onek koste korechi...sev0

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    string shortestCommonSupersequence(string str1, string str2) {
        auto commonSubSeq = helper(str1,str2);
        string ans = "";
        int idx = 0, idx1 = 0, idx2 = 0, m = str1.size(), n = str2.size();
        while((idx1<m) || (idx2<n)){
            if(idx1 >=m) ans.push_back(str2[idx2++]);
            else if(idx2 >=n) ans.push_back(str1[idx1++]);
            else {
                if(idx == commonSubSeq.size()) ans.push_back(str2[idx2++]);
                else {
                    if(commonSubSeq[idx] != str1[idx1]) ans.push_back(str1[idx1++]);
                    else if(commonSubSeq[idx] != str2[idx2]) ans.push_back(str2[idx2++]);
                    else {
                        ans.push_back(str2[idx2]);
                        idx++;
                        idx1++;
                        idx2++;
                    }
                }
            }
        }
        return ans;
    }

    string helper(string& str1, string& str2){
        int m = str1.size(), n = str2.size(), lasti = -1, lastj = -1, maxLen = 0;
        vvi dp(m+1,vi(n+1,0));
        string ans = "";
        for(auto i=1;i<=m;i++){
            for(auto j=1;j<=n;j++){
                if(str1[i-1] == str2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] +1;
                    if(maxLen < dp[i][j]) {
                        maxLen = dp[i][j];
                        lasti = i, lastj = j;
                    }
                } else {
                    dp[i][j] = max(dp[i][j-1],  dp[i-1][j]);
                }
            }
        }
        for(auto i=0;i<maxLen;i++){
            ans.push_back(str1[lasti-1]);
            lasti--;
            lastj--;
            while((lasti) && (lastj) && (str1[lasti-1] != str2[lastj-1] )) {
                if(dp[lasti][lastj-1] > dp[lasti-1][lastj]) lastj--;
                else lasti--;
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
