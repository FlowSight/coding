// 22 march 2025
// beaten by baxic concept..and not so much corner case..I took visited as well..
// sev0
// could not do bellman ford..forgot its purpose and code..


// theres a trick here..it textook bellman ford, its not required to take the tmp, as its guranteed to converge in v loops..here hops <=v
// hence for extra hops calculation we must take the tmp

class Solution {
    public:
        typedef vector<int> vi;
        typedef vector<vi> vvi;
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int hop) {
            vi dp(n,1e8);
            dp[src] = 0;
            int u,v,cost;
            
            for(auto k=0;k<=hop;k++){
                vi tmp = dp;
                for(auto &it : flights) {
                    u = it[0]; 
                    v = it[1]; 
                    cost = it[2];
                    tmp[v] = min(tmp[v],dp[u]+cost);
                }
                dp = tmp;
            }
            return dp[dst] == 1e8 ? -1 : dp[dst];
        }
    };

class Solution {
    public:
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
            vector<vector<int>> g(n+1,vector<int>(n+1,-1));
            multiset<vector<int>> ss; // {cost,hops,v}
            vector<vector<int>> visited(n,vector<int>(k+1,-1));
            for(auto &it : flights){
                auto u = it[0], v = it[1], cost = it[2];
                g[u][v] = cost;
                if(u == src){
                    ss.insert({cost,0,v});
                    visited[v][0] = cost;
                }
            }
    
            visited[src][0] = 0;
    
            while(!ss.empty()) {
                auto cur = *(ss.begin());
                ss.erase(ss.begin());
                auto cost = cur[0], hops = cur[1], v = cur[2];
                if(v == dst) return cost;
                if(hops == k) continue;
    
                for(auto i=0;i<n;i++){
                    if(g[v][i] == -1)continue;
                    auto newCost = cost + g[v][i];
                    if((visited[i][hops+1] != -1) && (visited[i][hops+1] <= newCost)) continue;
    
                    auto it = ss.find({visited[i][hops+1],hops+1,i});
                    if(it != ss.end()){
                        ss.erase(it);
                    }
                    visited[i][hops+1] = newCost;
                    ss.insert({newCost,hops+1,i});
                }
            }
            return -1;
        }
    };