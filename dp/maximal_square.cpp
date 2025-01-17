https://leetcode.com/problems/maximal-square/description/?envType=study-plan-v2&envId=top-interview-150


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans = 0;
        vvi dp(m,vi(n,0));
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                if(!i || !j || matrix[i][j] == '0') dp[i][j] = matrix[i][j]-'0';
                else {
                    dp[i][j] = min({dp[i-1][j-1],dp[i][j-1],dp[i-1][j]}) + 1;
                }
                ans = max(ans,dp[i][j]);
            }
        }
        return ans*ans;
    }
};


class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans = 0, lastJ_1 = 0;
        vi dp(n,0);
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                int tmp = dp[j];
                if(!i || !j || matrix[i][j] == '0') dp[j] = matrix[i][j]-'0';
                else {
                    dp[j] = min({lastJ_1,dp[j-1],dp[j]}) + 1;
                }
                ans = max(ans,dp[j]);
                lastJ_1 = tmp;
            }
        }
        return ans*ans;
    }
};