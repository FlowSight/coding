Given a map of cities where each city is connected by paths with a particular weight representing the cost of traversing that path. You are also provided with a list of favorite cities. Given a starting city, find one of the favorite cities such that the path cost from the starting city to this city is minimal. If there are multiple such cities, return all favorite cities with the minimum cost.

Input:

An integer n, the total number of cities.
An integer m, the total number of paths.
A list of m tuples edges, where each tuple (u, v, w) indicates a path with cost w between city u and city v.
An integer start, the starting city.
A list favorites, indicating the list of favorite cities.
Output:

A list containing all favorite cities with the minimum path cost from start.
Example:

Input:

5, 7, [[0, 1, 2], [0, 2, 4], [1, 2, 1], [1, 3, 7], [2, 3, 2], [3, 4, 3], [2, 4, 6]], 0, [3, 4]
Output:

[3]
Constraints:

1 <= n <= 1000
0 <= m <= 5000
0 <= w <= 10000
Example
Input
5, 7, [[0, 1, 2], [0, 2, 4], [1, 2, 1], [1, 3, 7], [2, 3, 2], [3, 4, 3], [2, 4, 6]], 0, [3, 4]