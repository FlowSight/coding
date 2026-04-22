Coding: Minimum Cost with Bundles/Offers (exact LC id unknown; referred as “LC 陆叁灞”)
Given:

price, where price[i] is the unit price of item i;
special, where each offer special[k] has length n+1: the first n numbers are quantities of each item and the last number is the offer price;
needs, the required quantities of each item.
You may buy offers any number of times and/or buy items individually. Compute the minimum total cost to satisfy needs.

Input (stdin)
Line 1: integer n
Line 2: n integers: price
Line 3: integer s (number of offers)
Next s lines: n+1 integers per line (one offer)
Last line: n integers: needs
Output (stdout)
A single integer: the minimum total cost
Constraints
1 <= n <= 6
0 <= needs[i] <= 10
0 <= price[i], special[*][*] <= 1000
0 <= s <= 100
Example
Input:

2
2 5
2
3 0 5
1 2 10
3 2
Output:

14
Highly similar to LeetCode 638. Shopping Offers.

Example
Input
2
2 5
2
3 0 5
1 2 10
3 2
Output
14