Given a transportation network with several locations and paths, each path has an associated transit cost. You need to start from a starting location and choose an optimal route to reach the target location such that the total transit cost is minimized. Write a program to calculate and return the minimum total transit cost. The input includes the number of locations, path data (starting point, endpoint, and transit cost for each path), and the output is the minimum transit cost.

Example Input:

5
0 1 10
1 2 5
2 3 2
0 3 15
Example Output:

17
Data Constraints:

Number of locations n: 1 <= n <= 1000
Transit cost c for each path: 1 <= c <= 10000
Example
Input
5
0 1 10
1 2 5
2 3 2
0 3 15