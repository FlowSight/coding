
// budles = {food items , cost}
// buy only once 
// want = lsit of items 

// min cost of cover 
// bm 
// for each bitmask, 
//     try for all items 
//         if included , skip 
//             newbm = bm | item bitmask
//             dp[newbm] = min(dp[newbm],dp[bm]+cost)
// tc = O(2^want) * bundles
// sc = O(2^want)

#include<bits/stdc++.h>

using namespace std;


typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<int> vi;
unordered_map<string, int> idxs;

int getbm(vs items){
    int ans = 0;
    for(auto it : items){
        ans = ans | (1<<idxs[it]);
    }
    return ans;
}
int getmincostcover(vvs bundles,vi cost, vs want ){
    int idx = 0, wantbm = 0, n = bundles.size(), ans = -1;
    for(auto it : bundles){
        for(auto it1 : it){
            if(idxs.find(it1) == idxs.end()) idxs[it1] = idx++;
        }
    }
    for(auto it : want) wantbm = wantbm | (1<<idxs[it]);
    vi dp(1<<idx,-1);
    dp[0] = 0;
    for(auto i=0;i<(1<<idx);i++){
        if(dp[i] == -1) continue;
        for(auto j=0;j<n;j++){
            int curbm = getbm(bundles[j]);
            if((i & curbm )== curbm) continue;
            int newbm = curbm | i;
            dp[newbm] = (dp[newbm] == -1) ? dp[i] + cost[j] : min(dp[newbm],cost[j] + dp[i]);
        }
        if((i & wantbm) == wantbm) ans = (ans == -1 ? dp[i] : min(ans,dp[i]));
    }
    return ans;
}

int main(){
    vvs bundles = {{"a","b","c"} ,{"d","e"}, {"a","c"}};
    vi cost = {5,2,1};
    vs want = {"a","c","d"};
    cout<<getmincostcover(bundles,cost,want)<<endl;
    return 0;
}