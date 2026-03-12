You are given a m*n grid matrix containing 'F': target, '#': obstacle, and '-': empty space. The 'F' target is fully connected. When dropped due to gravity, the target falls to the lowest point unless an 'F' contacts an obstacle. Return the grid state after the drop.

Input:
An array of strings grid of length m, each of length n.
Output:
An array of strings result_grid representing the grid state after the drop.
Example:
4 5
----F
--FF-
##---
-----
Example Output:
-----
-----
--FF-
##--F
Constraints:
1 <= m, n <= 100
Each cell contains 'F', '#', or '-'.
Example
Input
4 5
----F
--FF-
##---
-----