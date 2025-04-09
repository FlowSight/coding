There are Euler Path conditions that graphs must have:

For an undirected graph
- Every vertex should have an even degree or only two vertices should have odd degrees.
For a directed graph
 - Each vertex should have the same in-degree and out-degree except for two of them.
 - One of these vertex will be the start vertex which has one more out-going edge than in-going edges. The other one will be the end vertex which has one more in-going edge than out-going edges.


The following conditions determine whether a graph has an Eulerian Cycle or not on top of Eulerian Path conditions:

 For an undirected graph
 - Each vertex should have an even degree.
 For a directed graph
 - Every vertex should have equal in-degree and out-degree edges.


 to detect eulerian cycle via hierholzer algo : reconstruct itinerary