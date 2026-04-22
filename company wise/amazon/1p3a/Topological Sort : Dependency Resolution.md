Coding: Topological Sort (Dependency Resolution)
You are given n tasks labeled 0..n-1 and dependency pairs prerequisites. Each pair a b means you must complete b before a (a directed edge b -> a).

Determine whether all tasks can be finished:

Output YES if possible.
Output NO if there is a cycle.
Input (stdin)
Line 1: two integers n m (#tasks, #dependencies)
Next m lines: two integers a b meaning edge b -> a
Output (stdout)
One line: YES or NO
Constraints
1 <= n <= 2 * 10^5
0 <= m <= 2 * 10^5
0 <= a, b < n
Duplicate edges may exist
Examples
Input:

2 1
1 0
Output:

YES
Input:

2 2
1 0
0 1
Output:

NO
Example
Input
2 1
1 0
Output
YES