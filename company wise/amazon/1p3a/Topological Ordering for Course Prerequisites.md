Given the total number of courses n (labeled 0..n-1) and a list of prerequisite pairs prerequisites, where each pair [a, b] means you must complete course b before course a.

Return any valid ordering of the n courses that satisfies all prerequisites. If no such ordering exists, return an empty array.

Input Format
Line 1: integer n
Line 2: integer m number of prerequisite relations
Next m lines: two integers a b representing [a, b]
Output Format
If an ordering exists: print one line with n integers (space-separated) representing a valid order
Otherwise: print an empty line
Constraints
1 <= n <= 2 * 10^5
0 <= m <= 2 * 10^5
0 <= a, b < n
Duplicate edges may exist
Tests
Input:

4
4
1 0
2 0
3 1
3 2
Output (one valid example):

0 1 2 3
Input:

2
2
0 1
1 0
Output:

Input:

1
0
Output:

0
Input:

3
2
1 0
2 1
Output (one valid example):

0 1 2
Input:

3
1
2 2
Output:

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