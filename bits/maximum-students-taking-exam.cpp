/// Severity: Sev2
// Date: 29Jul26
// LC: 1349
// Where I failed: silly mistake, slow implementation
// Pattern: bm, dp
// Notes: additional_notes





class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size(), ans = 0;
        dp = vvi(2,vi(1<<n,0));
        for(auto i=1;i<=m;i++){
            for(auto j=0;j<(1<<n);j++){
                if(!isValid(j,seats[i-1])) continue;
                for(auto k=0;k<(1<<n);k++){
                    if(iscompatible(k,j,n)){
                        dp[1][j] = max(dp[1][j], dp[0][k] + getcount(j,n));
                    }
                }
                ans = max(ans,dp[1][j]);
            }
            dp[0] = dp[1];
        }
        return ans;
    }

    bool isValid(int& num, vector<char>& arr){
        int n = arr.size();
        for(auto i=0;i<n;i++){
            if((arr[i] == '#') && (num & (1<<i))) return false; // no position at broken seat
            if(i && (num & (1<<(i-1))) && (num & (1<<i))) return false; // no immediate position
        }
        return true;
    }

    bool iscompatible(int& num1, int& num2, int& n){
        for(auto i=0;i<n;i++){
            if(num1 & (1<<i)){
                // not on bottom left nd bottom right
                if((i+1 < n) && (num2 & (1<<(i+1)))) return false;
                if((i-1 >= 0) && (num2 & (1<<(i-1)))) return false;
            }
        }
        return true;
    }
    int getcount(int& num, int n){
        int ans = 0;
        for(auto i=0;i<n;i++){
            if(num & (1<<i)) ans++;
        }
        return ans;
    }
};


// dp[i][j] = till ith row, with ith row bm == j = whats the count
// ans = dp[n-1][j] sum over all j 