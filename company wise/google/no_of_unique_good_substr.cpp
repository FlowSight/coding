// 16jan2026..
// could not think of it..sev0

// dp[0] = nos ending with 0 len>=1
// dp[1] = nos ending with 1 len>=1
// the key is
// dp[1] will be having those members which ended with 0 i.e. dp[0]
//  those members are already part of dp[1]
//  then dp[1] will also add existing dp[1]
//  existing dp[1] already has all subseq ending with 1 including all parent and child ones
//  meaning, e.g.{ 1, 11, 111, 1111}, here 1111 --child of->111--child of->11--child of->1
//  when we do dp[1] = dp[0]+dp[1],we take all child and parents, hence existing 1 ending subseqs are considered also.
//  finally when we see a '1', we can start a new subseq with '1' alone, hence +1 for '1'
class Solution {
public:
    int mod = 1e9+7;
    int numberOfUniqueGoodSubsequences(string binary) {
        vector<int> dp(2,0);
        for(auto c: binary)dp[c-'0'] = (dp[0] + dp[1] + (c == '1'))%mod;
        return (dp[0] + dp[1] + (binary.find('0') != string::npos))%mod;
    }
};
