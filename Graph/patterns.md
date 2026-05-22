# Graph Patterns

## 1. BFS
- Unweighted shortest path from source — O(V+E)
- Level-order traversal, multi-source BFS (add all sources to queue initially)
- 0-1 BFS: deque-based, edges with weight 0 or 1
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

## 8. MST (Minimum Spanning Tree)
- Kruskal's: sort edges + DSU — O(E log E)
- Prim's: grow tree from source using min-heap — O(E log V)
- Use: minimum cost to connect all nodes, second-best MST

## 9. Strongly Connected Components (SCC)
- Tarjan's or Kosaraju's — O(V+E)
- Condensation: SCC → single node, forming a DAG
- Use: 2-SAT, reachability queries, finding bridges/articulation points

## 10. Bipartite / Matching
- Bipartite check: 2-color via BFS/DFS
- Hungarian algorithm or Hopcroft-Karp for maximum matching
- Use: job assignment, stable matching, graph coloring

## 11. Network Flow
- Max flow = min cut (Ford-Fulkerson, Edmonds-Karp O(VE^2), Dinic O(V^2*E))
- Use: maximum bipartite matching, min cut, circulation with demands

## 12. Euler Path / Hamiltonian Path
- Euler: visit every EDGE exactly once — exists if 0 or 2 odd-degree nodes
- Hamiltonian: visit every NODE exactly once — NP-complete (bitmask DP for small n)
- Use: reconstruct itinerary, Chinese postman problem

## Key Gotchas
- Directed vs undirected changes everything (cycle detection, connectivity)
- Sparse graph → adjacency list; dense → adjacency matrix
- For shortest path: no negative edges → Dijkstra; negative → Bellman-Ford; all pairs → Floyd
