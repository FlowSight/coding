/// Severity: Sev0
// Date: 06Sep26
// LC: 1192
// Where I failed: algo, disc vs dfs return
// mark disc/visited as some -x val as sometime u need to check -1 relation with current which can be 0
// Pattern: scc in undirected g
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vvi g;
    unordered_set<string> edges;
    vi disc;
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> ans;
        g = vvi(n,vi());
        disc = vi(n,-2);
        for(auto &it : connections) {
            g[it[0]].push_back(it[1]);
            g[it[1]].push_back(it[0]);
            edges.insert(getkey(it));
        }
        dfs(0,0);
        for(auto it : edges){
            vi cur;
            stringstream ss(it);
            string v;
            while(getline(ss,v,'#')){
                cur.push_back(stoi(v));
            }
            ans.push_back(cur);
        }
        return ans;
    }
    int dfs(int idx, int depth){
        if(disc[idx] >= 0) return disc[idx];
        int ans = disc[idx] = depth;
        for(auto v: g[idx]){
            if(disc[v] == depth-1) continue;
            auto discchild = dfs(v,depth+1);
            if(discchild <= disc[idx]){ // cycle
                auto key = getkey({idx,v});
                if(edges.find(key) != edges.end()) edges.erase(key);
            }
            ans = min(ans,discchild);
        }
        return ans;
    }

    string getkey(vi edge){
         sort(edge.begin(),edge.end());
         return to_string(edge[0]) + "#" + to_string(edge[1]);
    }
};