Problem: Build a relationship graph and answer reachability queries with BFS
You are given undirected relationships between entities and multiple queries. For each query (s, t), determine whether there exists a path from s to t following relationship edges.

Input (stdin)
First line: two integers n m — number of relationships and number of queries.
Next n lines: two strings u v — an undirected edge between u and v.
Next m lines: two strings s t — one query.
Output (stdout)
For each query output one line:

YES if t is reachable from s
NO otherwise
Constraints
1 <= n, m <= 2e5
Identifiers are alphanumeric/underscore strings, length 1..30
Must handle large input sizes
Example
Input:

4 3
A B
B C
D E
C A
A E
D E
Output:

YES
NO
YES
Example
Input
4 3
A B
B C
D E
C A
A E
D E
Output
YES
NO
YES