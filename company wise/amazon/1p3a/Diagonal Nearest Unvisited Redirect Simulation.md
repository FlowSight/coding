There are n servers on an infinite 2D plane, with coordinates locations[i] = [x_i, y_i]. You are also given an array redirectRecords of length q whose values are in 1..4, each denoting one redirection direction.

From a current server (a,b), the four directions are defined (where Z is any positive integer, Z ≥ 1):

Direction 1: (a,b) -> (a+Z, b+Z) (NE, slope +1)
Direction 2: (a,b) -> (a+Z, b-Z) (SE, slope -1)
Direction 3: (a,b) -> (a-Z, b+Z) (NW, slope -1)
Direction 4: (a,b) -> (a-Z, b-Z) (SW, slope +1)
Redirection rules:

The request starts at locations[0], which is marked visited initially.
For each direction in redirectRecords:
Consider only servers that lie on the corresponding diagonal ray in that direction (i.e., satisfy the diagonal and Z ≥ 1).
Redirect to the nearest server along that ray that has not been visited.
If no such server exists, the redirection is invalid and skipped (stay in place).
A server cannot be visited more than once.
After processing all q directions, return the final server coordinates [x, y].

Constraints

1 ≤ n ≤ 1e5
1 ≤ q ≤ 1e5
0 ≤ x_i, y_i ≤ 1e9
1 ≤ redirectRecords[i] ≤ 4
Example locations = [[3,4],[1,2],[7,8],[5,6]], redirectRecords = [1,4]. Start at (3,4). Under direction 1, the nearest unvisited server is (5,6). Under direction 4, go to (1,2). Return [1,2].

Example
Input
4
3 4
1 2
7 8
5 6
2
1 4
Output
1 2