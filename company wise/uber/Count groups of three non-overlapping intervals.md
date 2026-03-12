Given a list of intervals intervals, each interval is represented by two integer endpoints (l, r).

Definition: A triple of intervals is valid if the three intervals are pairwise non-overlapping.

Compute how many valid triples (groups of three) exist.

Input
First line: integer m, the number of intervals.
Next m lines: two integers l r describing an interval.
Output
Print a single integer: the number of valid triples.
Constraints
1 <= m <= 2e5
-1e9 <= l <= r <= 1e9
Examples
Example 1

4
1 2
3 4
5 6
7 8
Output

4
Example 2

4
1 3
2 4
5 7
6 8
Output

0
Example
Input
4
1 2
3 4
5 6
7 8
Output
4