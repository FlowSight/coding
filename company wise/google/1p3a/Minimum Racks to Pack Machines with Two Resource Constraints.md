Problem
You are given a list of N machines. The i-th machine consumes two types of resources (x_i, y_i).

Each rack has two capacity limits (a, b). For any rack, the sum of x requirements of machines placed on it must be <= a, and the sum of y requirements must be <= b.

You must assign every machine to exactly one rack (unlimited racks available).

Compute the minimum number of racks needed to fit all machines.

I/O (suggested)
Input: integer N, followed by N pairs (x_i, y_i), and capacities a, b.
Output: the minimum number of racks (integer).
Constraints / Notes
x_i, y_i, a, b are non-negative integers.
If there exists an i such that x_i > a or y_i > b, then packing is impossible (return -1 or as specified).
Example 1
N = 3
machines: (2,3), (3,2), (2,2)
rack capacity: (5,5)
Optimal packing:

rack1: (2,3) + (3,2) => (5,5)
rack2: (2,2)
Output: 2

Example 2
N = 4
machines: (4,1), (4,1), (1,4), (1,4)
capacity: (5,5)
Optimal packing:

rack1: (4,1) + (1,4) => (5,5)
rack2: (4,1) + (1,4) => (5,5)
Output: 2

Example
Input
3
2 3
3 2
2 2
5 5
Output
2