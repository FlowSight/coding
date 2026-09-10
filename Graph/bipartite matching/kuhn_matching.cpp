// Problem: left nodes 0..n1-1, right nodes 0..n2-1, edges only between the two sets.
// Find the MAXIMUM number of edges such that no node (either side) is used more than once.
//
// Complexity: O(V*E) -- for each of n1 left nodes, one DFS costs O(E) worst case.
// (Hopcroft-Karp improves this to O(E*sqrt(V)) via BFS-layered multi-augmenting-path phases,
//  but Kuhn's is the standard starting point.)

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// KUHN'S ALGORITHM
// ============================================================
// Core idea: process left nodes one at a time. For each left node u, try to find it
// SOME right-node partner via DFS. If a candidate right-node v is already matched to
// someone else, don't give up -- recursively ask "can v's current partner relocate to
// a different right-node instead?" If yes, that frees up v for u. This chain of
// "kick the current occupant, see if they can relocate" is an AUGMENTING PATH.
//
// Correctness (Berge's theorem): a matching is maximum iff no augmenting path exists.
// Each successful tryKuhn() strictly increases the matching size by 1; once no left
// node can find any augmenting path, the matching is maximum. (Bipartite matching is
// a special case of max-flow/min-cut with unit edge capacities -- same underlying idea.)
struct BipartiteMatching {
    int n1, n2;
    vector<vector<int>> adj;      // adj[u] = right-nodes u can connect to
    vector<int> matchL, matchR;   // matchL[u] = right partner of u (-1 if none)
                                   // matchR[v] = left partner of v (-1 if none)
    vector<bool> visited;         // guards against infinite loops within ONE augmenting attempt

    BipartiteMatching(int n1, int n2) : n1(n1), n2(n2), adj(n1), matchL(n1,-1), matchR(n2,-1) {}
    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool tryKuhn(int u) {
        for (int v : adj[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            // v is free, OR v's current partner can be reassigned elsewhere -> augment
            if (matchR[v] == -1 || tryKuhn(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int result = 0;
        for (int u = 0; u < n1; u++) {
            visited.assign(n2, false);   // reset per left-node attempt
            if (tryKuhn(u)) result++;
        }
        return result;
    }
};

// ============================================================
// Brute-force ground truth (for testing only): backtracking search over which
// left nodes to match and to which free right node, taking the best count found.
// Only feasible for small n1/n2.
// ============================================================
int bruteForceMaxMatching(int n1, int n2, vector<pair<int,int>>& edges) {
    vector<vector<bool>> canMatch(n1, vector<bool>(n2, false));
    for (auto& [u,v] : edges) canMatch[u][v] = true;

    int best = 0;
    function<void(int, int, vector<bool>&)> rec = [&](int u, int count, vector<bool>& usedRight) {
        if (u == n1) { best = max(best, count); return; }
        rec(u+1, count, usedRight);                  // option: leave u unmatched
        for (int v = 0; v < n2; v++) {                // option: match u to an available right node
            if (canMatch[u][v] && !usedRight[v]) {
                usedRight[v] = true;
                rec(u+1, count+1, usedRight);
                usedRight[v] = false;
            }
        }
    };
    vector<bool> usedRight(n2, false);
    rec(0, 0, usedRight);
    return best;
}

int main() {
    // ---- Manual sanity check: classic worker-job assignment example ----
    {
        BipartiteMatching bm(4, 4);
        bm.addEdge(0,0); bm.addEdge(0,1);
        bm.addEdge(1,0); bm.addEdge(1,2);
        bm.addEdge(2,1); bm.addEdge(2,2);
        bm.addEdge(3,3);
        int result = bm.maxMatching();
        cout << "Sanity check max matching: " << result << " (expected 4)\n";
        cout << "Matching pairs: ";
        for (int u = 0; u < 4; u++) cout << "(" << u << "->" << bm.matchL[u] << ") ";
        cout << "\n\n";
    }

    // ---- Randomized stress test vs brute force ----
    mt19937 rng(9);
    int mismatches = 0, trials = 3000;
    for (int t = 0; t < trials; t++) {
        int n1 = uniform_int_distribution<int>(1, 6)(rng);
        int n2 = uniform_int_distribution<int>(1, 6)(rng);
        vector<pair<int,int>> edges;
        for (int u = 0; u < n1; u++)
            for (int v = 0; v < n2; v++)
                if (uniform_int_distribution<int>(0,1)(rng)) edges.push_back({u,v});

        BipartiteMatching bm(n1, n2);
        for (auto& [u,v] : edges) bm.addEdge(u,v);
        int fast = bm.maxMatching();
        int brute = bruteForceMaxMatching(n1, n2, edges);

        if (fast != brute) {
            mismatches++;
            if (mismatches <= 5) cout << "MISMATCH: n1=" << n1 << " n2=" << n2 << " fast=" << fast << " brute=" << brute << "\n";
        }
    }
    cout << "Stress test: " << trials << " trials, " << mismatches << " mismatches\n";
    return 0;
}

// LeetCode applications:
// - LC 1820 (Maximum Number of Accepted Invitations): direct application, boys/girls bipartite matching.
// - LC 1066 (Campus Bikes II): bipartite ASSIGNMENT with cost minimization (Hungarian algorithm
//   variant -- min-cost matching rather than max-COUNT matching; different objective).
// - LC 785 (Is Graph Bipartite?): the CHECK (2-coloring via BFS/DFS) -- a prerequisite before
//   matching even makes sense; not matching itself.
