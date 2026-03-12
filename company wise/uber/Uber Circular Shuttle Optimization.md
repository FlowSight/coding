Uber has launched a new circular shuttle service that operates on a fixed route, starting and ending at the same location while collecting passengers from various designated stops.

The service area consists of n pickup locations, numbered from 0 to n-1. These locations are interconnected by roads, each with a uniform travel cost of 1 unit. The road network is defined by n-1 edges, where each edge [ai, bi] represents a bidirectional road connecting locations ai and bi. This configuration forms a connected tree structure of pickup locations.

Passenger demand is represented by an array of size n, where passengers[i] equals 1 if there's a passenger waiting at location i, and 0 otherwise.

The shuttle service operates as follows: The shuttle may begin its route at any pickup location. Two operations are available at each stop:

Passenger Collection (Cost: 0): Collect all passengers within a radius of 2 roads from the current location. The radius represents the maximum number of road segments the shuttle can reach to pick up passengers without additional cost.
Movement (Cost: 1): Travel to any directly connected pickup point, incurring a cost of 1 unit per road segment.
Objective: Determine the minimum total cost required to collect all waiting passengers and return the shuttle to its starting location.

Important Constraints:

Each time a road segment is traversed, it contributes 1 unit to the total cost (meaning a round trip on the same road costs 2 units).
The pickup locations form a valid tree structure (connected and acyclic).
Goal: Find the optimal starting location and route strategy that minimizes the total operational cost.

Note: If you pass a road 2 times, the cost to traverse that road becomes 2.

Function Description

Complete the function minimumShuttleCost in the editor.

minimumShuttleCost has the following parameters:

int[] passengers: A 1D array of integers where passengers[i] = 1 indicates a passenger at pickup point i, and passengers[i] = 0 indicates no passenger.
int[][] edges: A 2D array of integers where edges[i] = [ai, bi] indicates a bidirectional road connecting ai and bi.
Returns

int: Minimum cost incurred to start at a pickup point and return to the same starting point after collecting all the passengers from the pickup points.

Example
Input
passengers = [1, 0, 0, 0, 0, 1]
edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
Output
2