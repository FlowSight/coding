/// Severity: Sev0
// Date: 02Aug26
// LC: 2719
// Where I failed: implementation corner case
// Pattern: digit dp
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef vector<vvi> vvvi;
    typedef vector<vvvi> vvvvi;
    int mod = 1e9+7;
    int count(string num1, string num2, int min_sum, int max_sum) {
        int lenmin = num1.size(), lenmax = num2.size(), ans = 0;
        num1 = string(lenmax-lenmin,'0') + num1;

        // numbers smaller than num2 and digsum in range + 
        // numbers larger than num1 and digsum in range
        vvvvi dp3(lenmax+1,vvvi(max_sum+1,vvi(2,{-1,-1})));
        return helper3(num1,num2,dp3,0,0,1,1,min_sum, max_sum);
    }
    int helper3(string& num1, string& num2, vvvvi& dp, int idx, int cur_sum, int tight1, int tight2, int& min_sum, int& max_sum) {
        if(idx == num1.size()) return (cur_sum >= min_sum) && (cur_sum <= max_sum);
        if((cur_sum > max_sum)) return 0;
        if(dp[idx][cur_sum][tight1][tight2] != -1) return dp[idx][cur_sum][tight1][tight2];

        int ans = 0, dig1 = (num1[idx]-'0'), dig2 = (num2[idx]-'0');
        for(auto d=0;d<=9;d++){
            //if((idx == 0) && (d==0)) continue;
            int new_sum = cur_sum + d;
            if((new_sum > max_sum)) continue;
            if(tight1 && (d<dig1)) continue;
            if(tight2 && (d>dig2)) continue;
            ans = (ans +  helper3(num1,num2,dp,idx+1,new_sum,tight1 && (d == dig1), tight2 && (d == dig2), min_sum,max_sum))%mod;
        }
        return dp[idx][cur_sum][tight1][tight2] = ans;
    }
};