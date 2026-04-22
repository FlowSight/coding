You are given the total number of courses n (labeled 0..n-1) and a list of prerequisite pairs prerequisites, where each pair [a, b] means you must take course b before course a.

Return any valid ordering of courses (an array of length n) that satisfies all prerequisites. If it is impossible due to a cycle in the directed graph, return an empty array.

Requirements:

Must detect cycles in a directed graph.
Target time complexity close to O(n + m), where m is the number of prerequisite relations.
Typical interview constraints:

1 <= n <= 2 * 10^5
0 <= len(prerequisites) <= 2 * 10^5
Example:

Input: n = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] (or [0,2,1,3])
Example
Input
4
4
1 0
2 0
3 1
3 2
Output
0 1 2 3