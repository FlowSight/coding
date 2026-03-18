Given an integer N representing the number of stops/nodes, a list of routes, a start, an end, and several dangerous stops.

First task: Find the shortest path that does not pass through any dangerous stops. If no such path exists, return -1.

Second task: Find the shortest path that passes through the least number of dangerous stops.

Input:

An integer N representing the number of nodes (stations).
A list of tuples, each representing a valid route, including start, end, and step count.
An integer for the starting point.
An integer for the ending point.
A list of integers representing dangerous stops.
Output:

An integer representing the answer to the first task.
An integer representing the answer to the second task.
Constraints:

Data scale: 1 <= N <= 10^5
Each path step count is between 1 and 100.
If no path meets the conditions, return -1.
Example:

delivery_routes(3, [(0, 1, 10), (1, 2, 10), (0, 2, 20)], 0, 2, [1]) 
# Output: (20, 20)
Example
Input
3
[(0, 1, 10), (1, 2, 10), (0, 2, 20)]
0
2
[1]