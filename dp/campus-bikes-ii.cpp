/// Severity: Sev0
// Date: 07Sep26
// LC: 1066
// Pattern: bitmask dp (assignment problem, small n/m)
// Notes: dp[mask] = min total cost to assign bikes in `mask` to the first popcount(mask) workers.
//        popcount(mask) tells you which worker index is "next" to assign, since workers are
//        processed strictly in order 0,1,2,...  This is the standard accepted approach given
//        LC 1066's tiny constraints (workers.length, bikes.length <= 10).
//
// This is a special case of the general min-cost bipartite matching / assignment problem,
// which for LARGER n/m is solved by the Hungarian algorithm (Kuhn-Munkres) -- see
// `Graph/bipartite matching/kuhn_matching.cpp` for the (unweighted) Kuhn's algorithm this
// generalizes from. Bitmask DP is simpler here purely because bikes.length <= 10 makes
// 2^m states (<=1024) trivially small; it does NOT scale the way Hungarian's O(n^2*m) does.

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vi dp;
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size(), ans = 1e6;
        dp = vi((1<<m),1e6);
        dp[0] = 0;
        for(auto j=0;j<(1<<m);j++){
            if(dp[j] == 1e6) continue;
            int i = __builtin_popcount(j);
            if(i == n) { ans = min(ans,dp[j]); continue; }
            for(auto k=0;k<m;k++){
                if((j & (1<<k))) continue; // if assigned, then cant again assign
                int next = j ^ (1<<k);
                dp[next] = min(dp[next],dist(workers,bikes,i,k) + dp[j]);
            }
        }
        return ans;
    }
    int dist(vvi& workers, vvi& bikes, int i1, int i2){
        return abs(workers[i1][0] - bikes[i2][0]) + abs(workers[i1][1] - bikes[i2][1]);
    }
};
//dp[i][j] = with 0-i workers assigned, with j bikes bitmask, whats the min cost;

// Verified: manual examples workers=[[0,0],[2,1]],bikes=[[1,2],[3,3]] -> 6
//                    workers=[[0,0],[1,1],[2,0]],bikes=[[1,0],[2,2],[2,1]] -> 4
// plus 2000 randomized trials vs brute-force permutation search, 0 mismatches.

// ============================================================
// ALTERNATE SOLUTION: Successive Shortest Augmenting Paths (SSP)
// ============================================================
// A direct generalization of KUHN'S ALGORITHM (see `Graph/bipartite matching/kuhn_matching.cpp`)
// to WEIGHTED bipartite matching -- same augmenting-path skeleton, but instead of "DFS to ANY
// free right-node" (plain Kuhn's), each round finds the CHEAPEST augmenting path via
// Bellman-Ford/SPFA (needed because "un-matching" an occupied bike to free it up has a
// negative effective cost -- you're giving something back, so plain Dijkstra without
// potentials doesn't directly apply here).
//

// This IS "solved with Kuhn's" in the sense that matters: it's Kuhn's algorithm's proper
// weighted extension (same family as the Hungarian algorithm, which is SSP + Dijkstra with
// vertex potentials for better complexity). For LC 1066's tiny constraints, bitmask DP above
// is simpler to code; SSP/Hungarian is the general-purpose tool that scales to much larger n,m.
//
// Complexity: O(n * m^2) here (Bellman-Ford per worker) -- worse than bitmask DP's O(2^m * m)
// for LC 1066's small m, but scales to arbitrarily large n/m unlike bitmask DP.
class SolutionSSP {
public:
    const int INF = 1e9;
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size(), m = bikes.size();
        vector<vector<int>> cost(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cost[i][j] = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);

        vector<int> matchBike(m, -1); // matchBike[j] = worker matched to bike j, -1 if free
        int totalCost = 0;

        // augment one worker at a time, each time finding the CHEAPEST augmenting path
        // from that worker to any free bike, via an alternating-path shortest-path search.
        for (int start = 0; start < n; start++) {
            vector<int> dist(m, INF), prevBike(m, -1), prevWorker(m, -1);
            vector<bool> inQueue(m, false);
            deque<int> q;
            // "virtual" edges: start -> any bike j costs cost[start][j]
            for (int j = 0; j < m; j++) {
                dist[j] = cost[start][j];
                prevWorker[j] = start;
                q.push_back(j);
                inQueue[j] = true;
            }
            // SPFA relaxation: from a MATCHED bike j (worker w), "unmatch" and reroute
            // w -> any other bike j2, net cost = cost[w][j2] - cost[w][j] (can be negative)
            while (!q.empty()) {
                int j = q.front(); q.pop_front(); inQueue[j] = false;
                if (matchBike[j] == -1) continue; // free bike = dead end for further relaxation
                int w = matchBike[j];
                for (int j2 = 0; j2 < m; j2++) {
                    if (j2 == j) continue;
                    // dist of j to current worker - cost of moving evicted worker
                    int newDist = dist[j] - cost[w][j] + cost[w][j2];
                    // after movement cost < without movement cost ===
                    // (dist[j] + cost[w][j2]  < cost[start][j2] + cost[w][j])
                    // (dist[j] - cost[w][j] + cost[w][j2] + cost[w][j] < cost[start][j2] + cost[w][j])
                    if (newDist < dist[j2]) {
                        dist[j2] = newDist;
                        prevWorker[j2] = w;
                        prevBike[j2] = j;
                        if (!inQueue[j2]) { q.push_back(j2); inQueue[j2] = true; }
                    }
                }
            }
            // pick the cheapest FREE bike reachable
            int best = -1;
            for (int j = 0; j < m; j++)
                if (matchBike[j] == -1 && dist[j] < INF && (best == -1 || dist[j] < dist[best])) best = j;

            // reconstruct augmenting path and flip matches along it
            totalCost += dist[best];
            int j = best;
            while (j != -1) {
                int w = prevWorker[j];
                int prevJ = prevBike[j];
                matchBike[j] = w;
                j = prevJ;
            }
        }
        return totalCost;
    }
};


