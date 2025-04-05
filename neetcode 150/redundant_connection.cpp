// 26 feb 25..
// 8.30 mins
// no mistake
// dfs sol : could not come up..
// sev1

class UnionFind {
    public:
    int n,sz;
    vector<int> par, rank;
    UnionFind(int _n) {
        n = _n+1;
        sz = n;
        par = vector<int>(n,-1);
        rank = vector<int>(n,-1);
    } 
    void add(int u, int v){
        int parX = find(u), parY = find(v);
        int rankX = rank[parX], rankY = rank[parY];
        if(rankX == rankY) {
            rankY++;
            par[parX] = parY;
        } else if(rankX > rankY) {
            par[parY] = parX;
        } else {
            par[parX] = parY;
        }
    }

    int find(int u){
        return par[u] == -1 ? u : find(par[u]);
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind* uf = new UnionFind(n);
        for(auto &e : edges){
            if(uf->find(e[0]) == uf->find(e[1])) return e;
            uf->add(e[0],e[1]);
        }
        return {-1,-1};
    }
};


// dfs sol
class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vi ans;
    vector<int> cycle;
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vvi g = vvi(n+1,vi());
        vi vis(n+1,0);
        vi cur = {};

        for(auto &e : edges) {
            auto u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(g,vis,1,cur);
         for(auto i=n-1;i>=0;i--) {
            auto u = edges[i][0], v = edges[i][1];
            if ( (vis[u] == 2)  && (vis[v] == 2)) return edges[i]; 
         }
        return ans;
    }
    
    void dfs(vvi& g, vi& vis, int v, vi& cur,int par = -1){
        if(vis[v] == 2)return;
        if(vis[v]) {
            int n = cur.size();
            for(auto i=n-1;i>=0;i--){
                vis[cur[i]] = 2;
                if(cur[i] == v) break;
            }
            return;
        }
        vis[v] = 1;
        cur.push_back(v);
        for(auto &u : g[v]){
            if(u == par)continue;
            dfs(g,vis,u,cur,v);
        }
        cur.pop_back();
    }
};
