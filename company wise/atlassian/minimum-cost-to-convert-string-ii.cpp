//sev0..could not think of floydwasshall and one corner case


// this code TLE for large input, its okay..
// one optimization needed is size pooling
class Solution {
public:
    typedef vector<long long> vi;
    typedef vector<vi> vvi;
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        int m = source.size(), n = original.size(), maxLen = 0;
        unordered_map<string,int> idx;
        for(auto &it : original) reverse(it.begin(),it.end());
        for(auto &it : changed) reverse(it.begin(),it.end());
        // create index
        for(auto i =0;i<n;i++) {
            auto orig = original[i], tar = changed[i];
            maxLen = max(maxLen,(int)orig.size());
            if(idx.find(orig) == idx.end()) idx[orig] = idx.size();
            if(idx.find(tar) == idx.end()) idx[tar] = idx.size();
        }
        int sz = idx.size();
        vvi dist(sz,vi(sz,LONG_MAX));
        // init dist
        for(auto i=0;i<n;i++){
            auto orig = original[i], tar = changed[i];
            int idx1 = idx[orig], idx2 = idx[tar];
            dist[idx1][idx2] = min((long long) cost[i],dist[idx1][idx2]);
        }
        // fill dist using floyd warshall
        for(auto k=0;k<sz;k++){
            for(auto i=0;i<sz;i++){
                if(dist[i][k] == LONG_MAX) continue;
                for(auto j=0;j<sz;j++){
                    if(dist[k][j] == LONG_MAX) continue;
                    dist[i][j] = min(dist[i][k] + dist[k][j],dist[i][j]);
                }
            }
        }
        vi dp(m+1,LONG_MAX);
        dp[0] = 0;
        for(auto i=1;i<=m;i++){
            string orig = "", tar = "";
            if(source[i-1] == target[i-1]) {
                dp[i] = dp[i-1];
            }
            for(auto j=i;j>=1;j--){
                if(orig.size() == maxLen) break;
                orig.push_back(source[j-1]);
                tar.push_back(target[j-1]);
                if(dp[j-1] == LONG_MAX) continue;
                if(idx.find(orig) == idx.end()) continue;
                if(idx.find(tar) == idx.end()) continue;
                if(dist[idx[orig]][idx[tar]] == LONG_MAX) continue;
                dp[i] = min(dp[i],dist[idx[orig]][idx[tar]] + dp[j-1]);
            }
        }
        return dp[m] == LONG_MAX ? -1 : dp[m];
    }
};
