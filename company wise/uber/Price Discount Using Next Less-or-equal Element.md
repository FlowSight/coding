Problem: Price Discount (Next Less-or-equal Discount)
You are given an array prices of length n (1-indexed), where prices[i] is the original price of the i-th item.

For each index i, define its discount as the smallest index j such that:

j > i
prices[j] <= prices[i]
j is the smallest index satisfying the above (i.e., the first such item to the right)
Compute the final price final[i]:

If such j exists, final[i] = prices[i] - prices[j]
Otherwise, final[i] = prices[i]
Output the array final.

Input (stdin)
Line 1: integer n
Line 2: n integers, prices[1..n]
Output (stdout)
One line: n integers, final[1..n]
Constraints
1 <= n <= 2 * 10^5
1 <= prices[i] <= 10^9
Examples
Input:

5
8 4 6 2 3
Output:

4 2 4 2 3
Input:

4
1 2 3 4
Output:

1 2 3 4
Input:

4
10 1 1 6
Output:

9 0 1 6
Input:

1
7
Output:

7
Input:

6
5 5 5 5 5 5
Output:

0 0 0 0 0 5
Example
Input
5
8 4 6 2 3
Output
4 2 4 2 3