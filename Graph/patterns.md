# Graph Patterns

## 1. BFS
- Unweighted shortest path from source — O(V+E)
- Level-order traversal, multi-source BFS (add all sources to queue initially)
- 0-1 BFS: deque-based, use when every edge weight is only 0 or 1
- Rule: weight 0 edge → `push_front`, weight 1 edge → `push_back`
- Use: shortest path in grid, word ladder, rotten oranges, bipartite check

## 2. DFS
- Explore as deep as possible, backtrack
- Track visited, entry/exit times for subtree queries
- Use: cycle detection, connected components, topological sort, articulation points

## 3. Dijkstra
- Shortest path from source with non-negative weights — O((V+E) log V)
- Priority queue (min-heap) of (dist, node)
- **Gotcha**: don't re-process already finalized nodes
- Use: weighted shortest path, network delay time

## 4. Bellman-Ford / SPFA
- Handles negative weights — O(V*E)
- Relax all edges V-1 times; Vth iteration detects negative cycle
- SPFA: queue-based optimization (avg faster, worst same)
- Use: negative edges, arbitrage detection, shortest path with at most K edges

## 5. Floyd-Warshall
- All-pairs shortest path — O(V^3)
- dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]) for each intermediate k
- Use: small graphs (V ≤ 400), transitive closure, detecting negative cycles

## 6. Topological Sort
- DAG only — process nodes before their dependents
- Kahn's (BFS, indegree) or DFS (reverse postorder)
- Use: course schedule, build order, longest path in DAG

## 7. Union-Find (DSU)
- Near O(1) amortized union + find with path compression + rank
- Use: connected components dynamically, Kruskal's MST, cycle detection in undirected graph, accounts merge

## 8. Greedy DSU with Shared-First Edges
- When some edges help multiple consumers/graphs and others are exclusive, process shared edges first
- Reason: one useful shared union can replace multiple private unions later
- Keep an edge only if it merges two different DSU components; otherwise it is removable/redundant
- Often use two DSUs in parallel when two traversals/connectivity views must both stay valid
- Kruskal-like mindset: among useful edges, prioritize higher-coverage edges first
- Use: LC 1579 (remove max number of edges to keep graph fully traversable), multi-agent connectivity with shared resources

## 9. MST (Minimum Spanning Tree)
- Kruskal's: sort edges + DSU — O(E log E)
- Prim's: grow tree from source using min-heap — O(E log V)
- Use: minimum cost to connect all nodes, second-best MST

## 10. Strongly Connected Components (SCC)
- Tarjan's or Kosaraju's — O(V+E)
- Condensation: SCC → single node, forming a DAG
- Use: 2-SAT, reachability queries
- **Note**: SCC is a DIRECTED-graph concept only (mutual reachability needs direction to be meaningful). For UNDIRECTED graphs, the analogous "which edges/nodes are structurally critical" question is answered by Bridges / Articulation Points (see below), NOT by SCC — different check condition, different meaning.

## 10b. Bridges (Tarjan's Bridge-Finding, undirected graphs)
- An edge is a BRIDGE iff removing it increases the number of connected components (i.e. it's the only path between the two halves it connects)
- Reuses the same disc[]/low[] DFS machinery as Tarjan's SCC, but with a DIFFERENT check:
    - SCC root check: `low[u] == disc[u]` (u is the earliest-reachable anchor of its component)
    - Bridge check: `low[child] > disc[u]` (STRICT `>`) — child's subtree has NO way back to u or higher, not even to u itself
- **Gotcha — skip the parent edge**: undirected edges are bidirectional, so a plain DFS will immediately walk back from a child to its own parent via the same edge and mistake this for a cycle/back-edge. Must explicitly skip the edge back to the immediate parent (track by edge identity/index if there can be multiple parallel edges between the same two nodes, not just by node id, to avoid incorrectly skipping a genuine second edge)
- Articulation points (cut vertices): a related but distinct check — node u (non-root) is an articulation point if ANY child has `low[child] >= disc[u]` (non-strict; contrast with the strict `>` for bridges). Root of DFS tree is an articulation point iff it has 2+ children in the DFS tree.
- Use: LC 1192 (Critical Connections in a Network) — bridges; general "single point of failure" network analysis

## 11. Bipartite / Matching
- Bipartite check: 2-color via BFS/DFS
- Hungarian algorithm or Hopcroft-Karp for maximum matching
- Use: job assignment, stable matching, graph coloring

## 12. Network Flow
- Max flow = min cut (Ford-Fulkerson, Edmonds-Karp O(VE^2), Dinic O(V^2*E))
- Use: maximum bipartite matching, min cut, circulation with demands

## 13. Euler Path / Hamiltonian Path
- Euler: visit every EDGE exactly once — exists if 0 or 2 odd-degree nodes
- Hamiltonian: visit every NODE exactly once — NP-complete (bitmask DP for small n)
- Use: reconstruct itinerary, Chinese postman problem
- **Gotcha — Hamiltonian-shaped problem may actually be Euler in disguise**: if a problem gives you a list of pairs/tuples and asks you to arrange ALL of them into one valid sequence, it can look like "visit every item exactly once" (Hamiltonian-flavored, tempting you toward NP-complete search). Check whether each pair can instead be modeled as a directed EDGE `u→v` between the pair's two values — if so, "use every pair once" becomes "use every edge once" = Eulerian path, solvable in O(V+E) via Hierholzer's instead of exponential search. This reframing (item → edge, instead of item → node) is the key trick, not just "try Euler instead of Hamiltonian" — you must first see that the *pairs themselves* are the edges of a NEW graph over the original values, not that the pairs are nodes to be visited.
- Use: LC 2097 (Valid Arrangement of Pairs) — pairs ARE directed edges; find any valid Eulerian path over them

## Key Gotchas
- Directed vs undirected changes everything (cycle detection, connectivity)
- Sparse graph → adjacency list; dense → adjacency matrix
- Shortest-path choice:
- Unweighted edges → BFS
- Edge weights only 0/1 → 0-1 BFS
- Non-negative weighted edges (not restricted to 0/1) → Dijkstra
- Negative edge weights present → Bellman-Ford
- All-pairs shortest path on small graph → Floyd-Warshall
