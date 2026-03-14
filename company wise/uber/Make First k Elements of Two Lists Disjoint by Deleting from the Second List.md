Problem
You are given two integer arrays list1 and list2 (with lengths n1 and n2) and an integer k.

You may only delete elements from list2 (the relative order of the remaining elements must be preserved). Let list2' be the resulting array after deletions.

You must make sure that:

The first k elements of list1 and the first k elements of list2' are value-disjoint (i.e., no number appears in both length-k prefixes).
Return:

The minimum number of deletions required in list2.
If it is impossible (either list2' cannot have length k, or the constraint cannot be satisfied), return -1.
Input (stdin)
Line 1: n1 n2 k
Line 2: n1 integers for list1
Line 3: n2 integers for list2
Output (stdout)
One integer: the minimum deletions, or -1.
Constraints
1 <= n1, n2 <= 2e5
1 <= k <= min(n1, n2)
Elements are 32-bit signed integers
Examples
See the test cases in the Chinese statement.

Example
Input
3 5 2
1 2 3
2 4 1 5 6
Output
1