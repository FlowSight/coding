/// Severity: Sev1
// Date: 05Sep26
// LC: 802
// Where I failed: compiler error, exit condition on last 2 lines of dfs
// Pattern: dfs
// Notes: additional_notes



class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vi visited;
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        visited = vi(n,-1); // 0 : inprogress, 1 : safe,  3 : nonsafe
        // terminal = no outgoing,safe = all path to safe/terminal nodes
        for(auto i=0;i<n;i++){
            if(visited[i] == -1) dfs(graph,i);
        }
        vi ans;
        for(auto i=0;i<n;i++){
            if(visited[i] == 1) ans.push_back(i);
        }
        return ans;
    }

    int dfs(vvi& g, int idx){
        if(g[idx].size() == 0) return visited[idx] = 1;
        if(visited[idx] != -1) return visited[idx];
        visited[idx] = 0;
        for(auto v: g[idx]){
            auto res = dfs(g,v);
            if(res != 1) visited[idx] = 3;
        }
        if(visited[idx] == 0) visited[idx] = 1;
        return visited[idx];
    }
};