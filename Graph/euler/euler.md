There are Euler Path conditions that graphs must have:

Euler cycle : 

 For an undirected graph
 - Each vertex should have an even degree.
 For a directed graph
 - Every vertex should have equal in-degree and out-degree edges.


Euler path: 

 For an undirected graph
 - Each vertex should have an even degree (extra : OR or only two vertices should have odd degrees) 
 For a directed graph
 - Every vertex should have equal in-degree and out-degree edges (extra : OR except for two of them. One of these vertex will be the start vertex which has one more out-going edge than in-going edges. The other one will be the end vertex which has one more in-going edge than out-going edges.)


 to detect eulerian cycle via hierholzer algo : reconstruct itinerary

 Choosing the start vertex (directed graph, Hierholzer's):
 - If the graph has a valid Eulerian PATH (not cycle), exactly one vertex has out-degree = in-degree + 1 — that vertex MUST be the start (it has one extra outgoing edge with nowhere to "return" from).
 - If no such vertex exists (all vertices balanced in==out), the graph has an Eulerian CYCLE instead — any vertex with edges can be the start.
 - Implementation: scan all vertices with out-degree > 0; pick the one where out[v] > in[v] (or in.find(v)==in.end(), i.e. v never appears as a destination — same as in[v]==0 > out-nothing case); if none found, default to any vertex that has outgoing edges (e.g. the first edge's source).
 - **Gotcha**: after building the path via recursive Hierholzer's (post-order push to result), the result comes out in REVERSE — must reverse before reading off the final path/edge sequence.