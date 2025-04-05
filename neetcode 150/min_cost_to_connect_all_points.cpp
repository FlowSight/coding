// 22 march 2025
// forgot prim logic..failed
// sev0..
// did kruskal with 1 logic and 2 compiler errors



// another great logic

int minCostConnectPoints(vector<vector<int>>& ps) {
    int n = ps.size(), res = 0, i = 0, connected = 0;
    vector<int> min_d(n, 10000000);
    while (++connected < n) {
        min_d[i] = INT_MAX;
        int min_j = i;
        for (int j = 0; j < n; ++j)
            if (min_d[j] != INT_MAX) {
                min_d[j] = min(min_d[j], abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]));
                min_j = min_d[j] < min_d[min_j] ? j : min_j;
            }
        res += min_d[min_j];
        i = min_j;
    }
    return res;
}


// kruskal
class UnionFind {
    public:
        int n, comp;
        vector<int> par;
        UnionFind(int _n) {
            n = _n;
            comp = n;
            for(auto i=0;i<n;i++){
                par.push_back(i);
            }
        }

        void add(int u, int v){
            auto pU = find(u), pV = find(v);
            if(pU == pV) return;
            comp--;
            par[pU] = pV;
        }

        int find(int u){
            return par[u] == u ? u : find(par[u]);
        }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        UnionFind uf = UnionFind(n);
        priority_queue<vector<int>> pq; // {-cost,i,j};
        for(auto i=0;i<n;i++){
            for(auto j=i;j<n;j++){
                pq.push({-getDist(points[i],points[j]),i,j});
            }
        }
        while(!pq.empty() && (uf.comp>1)){
            auto tp = pq.top();
            pq.pop();
            auto cost = tp[0], u = tp[1], v = tp[2];
            auto parU = uf.find(u), parV = uf.find(v);
            if(parU == parV)continue;
            ans += -cost;
            uf.add(u,v);
        }
        return ans;
    }

    int getDist(vector<int>& p1, vector<int>& p2){
        return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1]);
    }
};

// prims

class Solution {
    public:
        int minCostConnectPoints(vector<vector<int>>& points) {
            int n = points.size(), ans = 0, cnt = 0;
            vector<vector<int>> g(n,vector<int>(n,0));
            for(auto i=0;i<n;i++){
                for(auto j=i;j<n;j++) {
                    g[i][j] = g[j][i] = getDist(points[i],points[j]);
                }
            }
            vector<int> visited(n,0);
            multiset<vector<int>> ss; // {dist,v}
            
            ss.insert({0,0});
            while(!ss.empty()) {
                auto cur = *(ss.begin());
                auto dist = cur[0], v = cur[1];
                ss.erase(ss.begin());
                
                if(visited[v]) continue;
    
                visited[v] = 1;
                ans += dist;
                cnt++;
    
                if(cnt == n) break;
    
                for(auto i=0;i<n;i++){
                    auto curDist = g[v][i];
                    if(!visited[i]) ss.insert({curDist,i});
                }
            }
            return ans;
        }
    
        int getDist(vector<int>& p1, vector<int>& p2){
            return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1]);
        }
    };