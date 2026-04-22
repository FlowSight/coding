Implement get(obj, path) to retrieve a value from a nested object made of arbitrary combinations of Maps (objects) and Arrays (lists), using a path string.

Path grammar:

. accesses a map key.
[...] accesses an array index (non-negative integer).
They can be chained, e.g. ab[1].c.d[2][13].
Input:

Line 1: a JSON value (objects/arrays/numbers/strings/bools/null).
Line 2: the path string.
Output:

Print the target value as JSON if it exists and the path is valid.
Otherwise print null.
Constraints:

Total nodes/elements N: 1 <= N <= 2e5
Path length L: 1 <= L <= 2e5
Aim for ~O(L) path parsing and iterative traversal.
Task: Parse the path and walk the structure step-by-step.

Example
Input
{"ab":[{"c":1},{"c":{"d":[0,1,[10,11,[100]]]} } ]}
ab[1].c.d[2][2][0]
Output
100