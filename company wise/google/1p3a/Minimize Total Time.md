You are given two integer arrays:

int[] multiples: the multipliers available in the shop
int[] prices: the corresponding prices for each multiplier
Both arrays have the same length n, and the i-th multiplier (multiples[i]) costs prices[i] coins to purchase.

You start with:

0 coins
A base gain rate of 1 coin per second
When you purchase a multiplier, your coin gain rate is multiplied by that value. For example:

Start: gain = 1x
Buy 3x -> gain becomes 3x
Buy 4x -> gain becomes 3 × 4 = 12x
You can only make purchases when you have enough coins to afford the multiplier.

Your goal is to purchase all the multipliers, in some order, such that the total time taken to finish all purchases is minimized.

Function Description

Complete the function minimizeTotalTime in the editor.

minimizeTotalTime has the following parameters:

int[] multiples: an array of multipliers available in the shop
int[] prices: an array of corresponding prices for each multiplier
Returns

int[]: an array of indices representing the order in which to purchase the multipliers to minimize the total time

Example
Input
multiples = [3, 100, 30]
prices = [5, 30, 15]
Output
[0, 2, 1]