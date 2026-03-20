Given a 2D array prerequisites where prerequisites[i] = [ai, bi] indicates that course ai depends on course bi being completed first, write a function to determine if it's possible to organize these courses. If it's possible, return a possible ordering of courses; otherwise, return an empty list.

Input:

n: number of total courses
prerequisites: a 2D array of course dependencies
Output:

A list representing a possible course order
Example:

Input: n = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]] Output: [0,1,2,3] or [0,2,1,3]

Constraints:

The number of courses is between [1, 1000].
There are no cyclic dependencies at any time.
Example
Input
4
[[1,0],[2,0],[3,1],[3,2]]