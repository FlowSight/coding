Problem
You are given a list of Uber rider logs sorted by time in ascending order. Each log entry indicates that two riders shared the same ride at a given time (shared-ride-with). If two riders shared a ride, they are directly connected. Connectivity is transitive: if A is connected to B and B is connected to C, then A is also connected to C.

Return the earliest timestamp such that all riders that ever appear in the logs become part of a single connected component after processing all events up to and including that timestamp.

Input format (suggested)
First line: integer m, the number of log entries.
Next m lines: each line
t name1 shared-ride-with name2 where t is an integer timestamp (or comparable time label), and name1/name2 are rider names (strings).
Logs are guaranteed to be sorted by increasing time (if the same timestamp occurs, process in input order).

Output format
Output the earliest time t when all riders are connected.
If they never become fully connected, output -1.
Example
Input (conceptual):

5
1 Alice shared-ride-with Bob
2 Charlie shared-ride-with Dan
3 Bob shared-ride-with Charlie
4 Alice shared-ride-with Evel
5 Bob shared-ride-with Dan
Output:

4
Explanation: By time 4, Alice/Bob/Charlie/Dan/Evel are all connected through ride-sharing relationships.

Constraints (suggested)
1 <= m <= 2*10^5
total distinct riders n: 1 <= n <= 2*10^5
An ~O(m α(n)) solution is expected (e.g., Union-Find / DSU).
Test cases (5)
Input:

5
1 Alice shared-ride-with Bob
2 Charlie shared-ride-with Dan
3 Bob shared-ride-with Charlie
4 Alice shared-ride-with Evel
5 Bob shared-ride-with Dan
Output:

4
Input:

3
1 A shared-ride-with B
2 C shared-ride-with D
3 A shared-ride-with C
Output:

3
Input:

2
10 A shared-ride-with B
20 C shared-ride-with D
Output:

-1
Input:

4
1 A shared-ride-with B
2 B shared-ride-with C
3 C shared-ride-with D
4 D shared-ride-with E
Output:

4
Input:

5
1 A shared-ride-with B
2 A shared-ride-with B
3 B shared-ride-with C
4 C shared-ride-with D
5 D shared-ride-with E
Output:

5
Example
Input
5
1 Alice shared-ride-with Bob
2 Charlie shared-ride-with Dan
3 Bob shared-ride-with Charlie
4 Alice shared-ride-with Evel
5 Bob shared-ride-with Dan
Output
4