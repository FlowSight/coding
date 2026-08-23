/// Severity: sev0
// Date: 22Aug26
// LC: 464
// Where I failed: sparse dp, base case, recurse error
// Pattern: bitmask dp / memoized game state search
// Notes: additional_notes

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    unordered_map<int,unordered_map<int,int>> dp;
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(maxChoosableInteger*(maxChoosableInteger+1)/2 < desiredTotal) return false;
        return helper(desiredTotal,0,0,maxChoosableInteger);
    }

    bool helper(int& rem, int player, int bitmask, int& maxChoosableInteger){
        if((dp.find(rem) != dp.end()) && (dp[rem].find(bitmask) != dp[rem].end())) return dp[rem][bitmask];
        int res = 0;
        for(auto i=1;i<=maxChoosableInteger;i++){
            if((bitmask & (1<<i)) == 0) {
                int tmp = rem - i;
                if((tmp <= 0) || (!helper(tmp,(player ^ 1),(bitmask | (1<<i)), maxChoosableInteger))) {
                    return dp[rem][bitmask] =  1;
                }
            }
        }
        return dp[rem][bitmask] = res;
    }
};
