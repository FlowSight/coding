Note See source image below for the original statement :)

Imagine you’re working with an endless number line and want to place obstacles and check if you can build blocks on it. You have two types of tasks: one allows you to place an obstacle at a specific point, ensuring that spot is free when you do so. The other lets you check if it's possible to build a block of a certain size ending just before a given point, making sure there are no obstacles in the way. Your goal is to process a list of these tasks and return a string of "1"s and "0"s, where each "1" means you can build the block, and each "0" means you can't.

** Shoutout for Charlotte baby **

Constraints:

All coordinates within operations are within the following interval [-109, 109
The size from the second type of operation are positive integers which would not exceed 109
1 <= operations.length <= 105
A binary string representing the outputs for all [2, x, size] operations
Example
Input
operations = [[1, 2], [1, 5], [2, 5, 2], [2, 6, 3], [2, 2, 1], [2, 3, 2]]
Output
"1010"