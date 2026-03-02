You are dining at a restaurant and provided with a menu containing prices of different dishes. You need to order some dishes such that the total cost exactly equals to a specific amount. Each dish can be ordered multiple times. Write an algorithm to compute the total count of different ways to order meals that sum up to the exact budget.

Input Description:

An integer list prices, representing the cost of each dish.
An integer amount, representing the dining budget.
Output Description:

An integer representing the number of different ordering combinations that sum up to the amount.
Example 1:

Input: prices = [1, 2, 5], amount = 5
Output: 4
Explanation: The different combinations are:
5 = 5
5 = 2 + 2 + 1
5 = 2 + 1 + 1 + 1
5 = 1 + 1 + 1 + 1 + 1
Constraints:

The number of elements in prices is up to 500
Each dish price does not exceed 300
The amount does not exceed 10^4
Example
Input
[1, 2, 5]
5