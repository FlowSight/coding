//works on graph with no negative weight cycles

for (int k = 0; k < V; k++)
{
    // Pick all vertices as source one by one
    for (int i = 0; i < V; i++)
    {
        // Pick all vertices as destination
        // for the above picked source
        for (int j = 0; j < V; j++)
        {
            // shortest path from
            // i to j
            if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
}
if(dist[i][i] < 0) {
    // negative cycle detected
    return {};
}