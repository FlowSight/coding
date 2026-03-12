At the Robotics Innovation Campus "UBERBOT", Unit IG-0R is a vertical wall-climbing robot that can scale surfaces using embedded magnetic contact points (nodes). The robot is deployed on a vertical metal wall designed as a rectangular grid with:

n horizontal levels (rows)
m segments per level (columns)
Each segment is either:

'X' (node the robot can use)
'#' (empty space)
Valid Route Criteria

Start: The first node must be on the bottommost level (row n).
End: The last node must be on the topmost level (row 1).
Level-by-Level Progression: The robot may only move upward or horizontally; it cannot move to a lower level. The robot must access at least one node per level to recharge its navigation sensors.

Node Usage per Level: The robot can use up to two nodes per level (due to sensor synchronization constraints). These nodes can be used in any order, but each node is visited at most once in a route.

Battery Constraint: IG-0R's battery capacity allows it to jump only between nodes whose Euclidean distance is less than or equal to w, unit range.

The distance between two nodes at positions (i1, j1) and (i2, j2) is computed as: sqrt((i1 - i2)^2 + (j1 - j2)^2)

The robot cannot transition between nodes if the computed distance exceeds its battery limit w. w >= sqrt((i1 - i2)^2 + (j1 - j2)^2)

Function Description

Complete the function countRoutes in the editor.

countRoutes has the following parameters:

1. char[][] grid: a 2D array of characters representing the grid
2. w: an integer representing the maximum Euclidean distance the robot can jump
Returns

int: the number of distinct valid routes, computed modulo 998244353

Example
Input
grid = [
            ['X', 'X', '#', 'X'],
            ['#', 'X', 'X', '#'],
            ['#', 'X', '#', 'X']
          ]
w = 1
Output
2