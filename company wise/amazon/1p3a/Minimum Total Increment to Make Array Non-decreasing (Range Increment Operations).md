Given an integer sequence A = [a1, a2, ..., an] of length n, you may perform any number of operations. In each operation:

Choose a closed interval [i, j] (1 <= i <= j <= n)
Choose a positive integer x
Increase every element a_k for i <= k <= j by x
After all operations, the sequence must be non-decreasing: a_i <= a_{i+1}.

Minimize the sum of all chosen increments x across operations:

minimize Σ x.

Return this minimum value.

Constraints

1 <= n <= 2*10^5
-10^9 <= a_i <= 10^9
Example

Input: [3, 1, 2]
Output: 3
Example
Input
3
3 1 2
Output
3