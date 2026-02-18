//sev0..sev0..could not think of dp 
// 2 fai poiints: dp and one sneaky little trick in the end 

class Solution {
public:
    typedef vector<string> vs;
    typedef vector<vs> vvs;
    string encode(string s) {
        int n = s.size();
        vvs dp(n,vs(n,""));

        for(auto len = 1;len<=n;len++){
            for(auto i=0,j=i+len-1;(i+len-1<n);i++,j=i+len-1){
                dp[i][j] = s.substr(i,len);
                if(len<=4) continue;
                for(auto k=i;k<j;k++){
                    if(dp[i][k].size() + dp[k+1][j].size() < dp[i][j].size()){
                        dp[i][j] = dp[i][k] + dp[k+1][j];
                    }
                }
                for(auto subStrLen = 1;subStrLen<=len/2;subStrLen++){
                    if(len%subStrLen) continue;
                    int idx=i+subStrLen;
                    string substr = s.substr(i,subStrLen);
                    while(idx<=j){
                        auto str = s.substr(idx,subStrLen);
                        if(str != substr) break;
                        idx += subStrLen;
                    }
                    if((idx >j)) {
                        auto encoded = to_string(len/subStrLen)+ "["+dp[i][i+subStrLen-1] + "]";
                        if(encoded.size() < dp[i][j].size()){
                            dp[i][j] = encoded;
                        }
                    }
                }
            }
        }
        return dp[0][n-1];
        
    }
};