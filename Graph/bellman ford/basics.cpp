vector<int> bellmanFord(int n, vector<Edge>& edges, int src) {
    const int INF = numeric_limits<int>::max() / 2;
    vector<int> dist(n, INF);
    dist[src] = 0;

    // Relax all edges n-1 times
    for (int i = 1; i < n; ++i) {
        for (auto& e : edges) {
            if (dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;
            if (dist[e.v] + e.w < dist[e.u])
                dist[e.u] = dist[e.v] + e.w;
        }
    }
    // Optional: Check for negative cycles
    for (auto& e : edges) {
        if (dist[e.u] + e.w < dist[e.v] || dist[e.v] + e.w < dist[e.u]) {
            cout << "Negative weight cycle detected!" << endl;
            break;
        }
    }
    return dist;
}



arbitrage problem

w1*w2*w3*...*wn > 1
-logw1 -logw2 -logw3 -...-logwn < 0
convert all weights to -logw
then find negative cycle in graph
use bellman ford algo

if negative cycle exists, then arbitrage exists
if not, then no arbitrage exists
