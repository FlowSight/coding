Given an integer array where the i-th element represents the price of a stock on day i. Your task is to design an algorithm to find the maximum profit you can achieve by buying and selling a single stock. Note: You cannot sell a stock before you buy one.

Input:

A list of n integers representing stock prices.
Output:

An integer representing the maximum profit you can achieve. If no profit can be achieved, return 0.
Example:

Input: [7, 1, 5, 3, 6, 4]
Output: 5
Explanation: Buy on day 2 (price=1) and sell on day 5 (price=6), profit = 6-1 = 5. Note you cannot achieve 7-1=6 because selling price needs to be after the buying day.

Input: [7, 6, 4, 3, 1]
Output: 0
Explanation: In this case, no transactions are done, profit = 0.
Constraints:

1 <= n <= 10^5.
0 <= prices[i] <= 10^4.
Example
Input
[7, 1, 5, 3, 6, 4]