Problem: Reachability Under a Distance Threshold (Implicit Graph)
You are given a set of unordered 2D points points, each represented as (x, y). You are also given:

Start coordinate S = (sx, sy)
Target coordinate T = (tx, ty)
A positive threshold r
A black-box function getDistance(p, q) that returns the distance between two points p and q
Define adjacency as follows:

If getDistance(p, q) < r, then p and q are mutually reachable (i.e., there is an undirected edge between them).
Determine whether there exists a path from S to T by repeatedly moving between points whose distance is < r.

Input Format (suggested)
Line 1: integer N
Next N lines: two numbers xi yi per line
Next line: sx sy
Next line: tx ty
Next line: r
Output Format
Print true or false
Notes
You may assume getDistance is available, but calls may be expensive; try to avoid redundant calls.
Sample Tests
input:

3
0 0
1 0
2 0
0 0
2 0
1.1
output:

true
input:

3
0 0
1 0
2 0
0 0
2 0
1.0
output:

false
input:

1
5 5
0 0
5 5
10
output:

true
input:

4
0 0
0 2
2 0
2 2
0 0
2 2
1.5
output:

false
input:

5
0 0
0 1
0 2
0 3
0 4
0 0
0 4
1.01
output:

true
Example
Input
3
0 0
1 0
2 0
0 0
2 0
1.1
Output
true