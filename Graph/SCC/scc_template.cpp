
// Both O(V+E)
// SCC definition: maximal set of vertices where every pair (u,v) has BOTH
// u->v and v->u paths (mutual reachability). 
// A DAG's SCCs are each single nodes.***

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// TARJAN'S ALGORITHM — single DFS pass
// ============================================================
// Each node gets a 
// discovery time (disc[]) and 
//  "low-link" value (low[]) = smallest discovery time reachable from that node's subtree via **at most ONE**
// back-edge to an ancestor still on the stack. A node is the ROOT of an SCC iff
// low[node] == disc[node] (nothing in its subtree reaches further back than itself).
// Maintain an explicit stack of "currently active" nodes; on finding an SCC root,
// pop everyone down to it off the stack — that's exactly one SCC.
struct Tarjan {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> disc, low;
    vector<bool> onStack;
    stack<int> st;
    vector<vector<int>> sccs;

    Tarjan(int n) : n(n), adj(n), disc(n, -1), low(n, -1), onStack(n, false) {}
    void addEdge(int u, int v) { adj[u].push_back(v); }

    stack<int>  getComponent() {
        return st;
    }

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        onStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {                      // v unvisited -> tree edge
                dfs(v);
                low[u] = min(low[u], low[v]);          // pull up child's low-link
            } else if (onStack[v]) {                   // v visited AND still on stack -> back edge
                low[u] = min(low[u], disc[v]);         // use disc[v], NOT low[v] (v not fully resolved yet)
            }
            // v visited but NOT on stack -> v belongs to an already-finished SCC, ignore
        }

        if (low[u] == disc[u]) {                       // u is a root of an SCC
            vector<int> component;
            while (true) {
                int w = st.top(); st.pop();
                onStack[w] = false;
                component.push_back(w);
                if (w == u) break;
            }
            sccs.push_back(component);
        }
    }

    vector<vector<int>> run() {
        
        for (int i = 0; i < n; i++) if (disc[i] == -1) dfs(i);
        return sccs;
    }
};

// ============================================================
// KOSARAJU'S ALGORITHM — two DFS passes
// ============================================================
// 1) DFS the original graph, push nodes to a stack in FINISH order (postorder).
// 2) Build the transpose graph (reverse every edge).
// 3) Pop nodes off the stack (decreasing finish-time order); for each unvisited
//    node, DFS on the TRANSPOSE — everything reached in that DFS is one SCC.
// Why it works: starting from the node with the LATEST finish time in the
// original graph guarantees the transpose-DFS can't "leak" into a different SCC
// that the original node can't actually reach back from.
// simpler explanation : if a node is reachable after transposing, but was not in original graph, 
// then its not in same scc, vice versa. in dfs2,such components will be disconnected.
struct Kosaraju {
    int n;
    vector<vector<int>> adj, radj; // radj = reverse/transpose graph
    vector<bool> visited;
    stack<int> finishOrder;
    vector<vector<int>> sccs;

    Kosaraju(int n) : n(n), adj(n), radj(n), visited(n, false) {}
    void addEdge(int u, int v) { adj[u].push_back(v); radj[v].push_back(u); }

    void dfs1(int u) {
        visited[u] = true;
        for (int v : adj[u]) if (!visited[v]) dfs1(v);
        finishOrder.push(u);          // push AFTER exploring all neighbors (postorder)
    }
    void dfs2(int u, vector<int>& component) {
        visited[u] = true;
        component.push_back(u);
        for (int v : radj[u]) if (!visited[v]) dfs2(v, component);
    }

    vector<vector<int>> run() {
        for (int i = 0; i < n; i++) if (!visited[i]) dfs1(i);
        fill(visited.begin(), visited.end(), false);
        while (!finishOrder.empty()) {
            int u = finishOrder.top(); finishOrder.pop();
            if (!visited[u]) {
                vector<int> component;
                dfs2(u, component);
                sccs.push_back(component);
            }
        }
        return sccs;
    }
};

// ============================================================
// Brute-force ground truth (for testing only): SCC = mutual reachability
// equivalence classes. u,v in same SCC iff u can reach v AND v can reach u.
// ============================================================
vector<vector<int>> bruteForceSCC(int n, vector<pair<int,int>>& edges) {
    vector<vector<int>> adj(n);
    for (auto& [u,v] : edges) adj[u].push_back(v);

    auto reachableFrom = [&](int src) {
        vector<bool> vis(n, false);
        queue<int> q; q.push(src); vis[src] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) if (!vis[v]) { vis[v] = true; q.push(v); }
        }
        return vis;
    };

    vector<vector<bool>> reach(n);
    for (int i = 0; i < n; i++) reach[i] = reachableFrom(i);

    vector<int> compId(n, -1);
    vector<vector<int>> comps;
    for (int i = 0; i < n; i++) {
        if (compId[i] != -1) continue;
        vector<int> comp = {i};
        compId[i] = comps.size();
        for (int j = i+1; j < n; j++) {
            if (compId[j] == -1 && reach[i][j] && reach[j][i]) {
                compId[j] = comps.size();
                comp.push_back(j);
            }
        }
        comps.push_back(comp);
    }
    return comps;
}

// Normalize: sort each component, sort list of components -> for set-equality comparison
vector<vector<int>> normalize(vector<vector<int>> sccs) {
    for (auto& c : sccs) sort(c.begin(), c.end());
    sort(sccs.begin(), sccs.end());
    return sccs;
}

int main() {
    // ---- Manual sanity check on a classic textbook example ----
    // Graph: two 3-cycles (0-1-2 and 3-4-5) chained together, plus a tail (6->7)
    {
        int n = 8;
        vector<pair<int,int>> edges = {{0,1},{1,2},{2,0},{2,3},{3,4},{4,5},{5,3},{5,6},{6,7}};
        Tarjan t(n); for (auto& [u,v]: edges) t.addEdge(u,v);
        Kosaraju k(n); for (auto& [u,v]: edges) k.addEdge(u,v);

        auto sccT = normalize(t.run());
        auto sccK = normalize(k.run());
        auto sccB = normalize(bruteForceSCC(n, edges));

        cout << "Tarjan SCCs: ";
        for (auto& c : sccT) { cout << "{ "; for (int x : c) cout << x << " "; cout << "} "; }
        cout << "\nKosaraju SCCs: ";
        for (auto& c : sccK) { cout << "{ "; for (int x : c) cout << x << " "; cout << "} "; }
        cout << "\nBrute force SCCs: ";
        for (auto& c : sccB) { cout << "{ "; for (int x : c) cout << x << " "; cout << "} "; }
        cout << "\nAll match: " << (sccT == sccB && sccK == sccB ? "YES" : "NO") << "\n\n";
    }

    // ---- Randomized stress test: Tarjan vs Kosaraju vs brute force ----
    mt19937 rng(42);
    int mismatches = 0, trials = 3000;
    for (int t = 0; t < trials; t++) {
        int n = uniform_int_distribution<int>(1, 8)(rng);
        int e = uniform_int_distribution<int>(0, n * n)(rng);
        vector<pair<int,int>> edges;
        for (int i = 0; i < e; i++) {
            int u = uniform_int_distribution<int>(0, n-1)(rng);
            int v = uniform_int_distribution<int>(0, n-1)(rng);
            edges.push_back({u, v});
        }

        Tarjan tar(n); for (auto& [u,v] : edges) tar.addEdge(u,v);
        Kosaraju kos(n); for (auto& [u,v] : edges) kos.addEdge(u,v);

        auto sccT = normalize(tar.run());
        auto sccK = normalize(kos.run());
        auto sccB = normalize(bruteForceSCC(n, edges));

        if (sccT != sccB || sccK != sccB) {
            mismatches++;
            if (mismatches <= 3) cout << "MISMATCH on trial " << t << " (n=" << n << ", e=" << e << ")\n";
        }
    }
    cout << "Stress test: " << trials << " trials, " << mismatches << " mismatches\n";
    return 0;
}
