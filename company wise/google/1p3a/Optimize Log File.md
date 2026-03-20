A log file contains a series of entries represented by a permutation of length n integers. To analyze the log efficiently, n operations, indexed from 0 to n-1, are available. Each operation involves swapping two entries in the log. The goal is to select some of these n operations and apply them in any order to the log entries to produce the lexicographically smallest permutation, facilitating a more streamlined log analysis. The task is to return this lexicographically smallest permutation of entries.

Additional notes:- Each operation can be used at most once.

0-based indexing is considered.
A permutation is an array consisting of distinct integers from 1 to n in arbitrary order.
The permutation p of length n is lexicographically less than the permutation q of length n if there is an index i such that for all j from 0 to i-2, the condition p[j] = q[j] is satisfied, and p[i] < q[i].
Constraints:

1 < n <= 2 * 10^5
1 ≤ entries[i] < n
It is guaranteed that the array entries is a permutation of length n.
Example
Input
entries = [5, 4, 1, 3, 2]
Output
[1, 5, 2, 4, 3]