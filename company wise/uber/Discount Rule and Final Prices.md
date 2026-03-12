Given an array prices where prices[i] represents the price of the i-th item, apply a discount for each item based on the next minimum price that's not greater than itself on the right side. Output the total price and the indices of items sold at original prices.

Example:

Input: prices = [8, 4, 6, 2, 3] Output: 14\n0 3

Explanation: Final Prices are [4, 2, 4, 2, 3] Original Price Indices are [0, 3]

Constraints:

1 <= prices.length <= 10^5
1 <= prices[i] <= 10^9
Example
Input
5
[8, 4, 6, 2, 3]
Output
14\n0 3