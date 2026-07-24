/// Severity: Sev0
// Date: 16Jul26
// LC: 902
// Where I failed: tight condition + start condition + slow implementation
// Pattern: digit dp
// Notes: additional_notes



// digit dp : start with tight
// i make mistake in tight calculation

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi dp;
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string num = to_string(n);
        int sz = num.size(), len = digits.size(), ans = 0;
        for(auto i=1;i<sz;i++) ans += pow(len,i);
        dp = vvi(sz,{-1,-1});
        return ans + helper(digits,num,0,1);
    }
    int helper(vector<string>& digits,string& target, int idx, int tight){
        if(idx == target.size()) return 1;
        if(dp[idx][tight] != -1) return dp[idx][tight];
        int ans = 0;
        for(auto i=0;i<digits.size();i++){
            if(digits[i][0] <= target[idx]) ans += helper(digits,target,idx+1, tight && (digits[i][0] == target[idx]));
            else if(!tight){
                 ans += helper(digits,target,idx+1,0);
            } else break;
        }
        return dp[idx][tight] = ans;
    }
};

