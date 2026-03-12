Problem
You are given n balls on a 2D plane with coordinates (x_i, y_i) and a distance threshold d.

Define the Euclidean distance: [ dist(i,j) = \sqrt{(x_i-x_j)^2 + (y_i-y_j)^2} ]

If dist(i, j) < d, then ball i and ball j are considered mutually attractive. This attraction triggers a chain reaction: if a ball can attract another ball directly or through a sequence of intermediate balls, they belong to the same attraction connected component.

At each time step, you may choose one ball to start the attraction process, which will merge/finish the entire connected component containing that ball in that single step.

Return the minimum number of time steps required to make all balls get attracted/merged (i.e., finish all balls).

Input
First line: two integers n and d
Next n lines: two integers x_i y_i
Output
A single integer: the minimum number of steps.
Constraints
1 <= n <= 2000
Coordinates are integers within 32-bit range
d is a positive integer
Use strict inequality < d (not <= d).
Example 1
Input:

4 3
0 0
0 2
10 10
11 10
Output:

2
Example 2
Input:

3 2
0 0
0 2
3 0
Output:

3
Example
Input
4 3
0 0
0 2
10 10
11 10
Output
2