You are given a binary array product of length n and a positive integer k. You want to convert all 1s to 0s with minimum total cost.

You may repeat the following operation:

Choose a subarray [l, r] of length exactly k (so r - l + 1 = k).
The cost of this operation is sum(product[l..r]).
Then choose an index p in [l, r] such that product[p] = 1 and set it to 0.
When there are no 1s left, the process ends. Return the minimum possible total cost.

Suggested Input
Line 1: n
Line 2: product (n integers 0/1)
Line 3: k
Output
Minimum total cost.
Constraints (typical)
1 <= n <= 2e5, 1 <= k <= n, product[i] in {0,1}
Example
Input
5
1 0 1 1 0
3
Output
(unknown)