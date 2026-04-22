The manager of the Amazon warehouse has decided to make changes to the inventory by adjusting the prices of the products. Currently, the inventory has n products, where the price of the i-th product is represented by prices[i]. The manager is given two integers:

k — the maximum amount by which a product’s price can be adjusted (increased or decreased) in a single operation
d — the target price difference
The goal is to ensure that the difference between the highest and lowest prices in the inventory is strictly less than d.

Allowed Operation:

Select two indices x, y (1 ≤ x ≤ y ≤ n), and an integer p (1 ≤ p ≤ k)
Increase the price of the product at index x by p.
Decrease the price of the product at index y by p.
Given:

integer n
array prices
integers k and d Find the minimum number of operations required for the maximum difference between the prices of any two products to become strictly less than d. Note: prices uses 1-based indexing in the problem description.
Input:

An integer n.
An integer array prices representing product prices.
Integers k and d.
Output:

The minimum number of operations required to reach the target price difference.
Example:

Input: n = 3, prices = [1, 5, 9], k = 3, d = 4
Output: 2
Explanation: The following operations can be performed:
1. Increase price[1] to 4, decrease price[3] to 6.
2. Increase price[1] to 7, decrease price[3] to 8.
The difference is |5-7|, less than d=4.
Constraints:

2 <= n <= 1000
1 <= prices[i] <= 100000
0 < k <= 100000
0 < d <= 100000
Example
Input
3
1 5 9
3 4