Given a 2D matrix containing integers 1, 2, and 0, find the length of the longest diagonal pattern in the matrix. The pattern starts with 1 and then alternates between 2 and 0. The diagonal can be either from top-left to bottom-right or bottom-left to top-right, without changing direction. Output the length of the longest pattern that meets these criteria.

Input Format:

int[][] matrix: An integer matrix where each element is either 1, 2, or 0.
Output Format:

An integer representing the length of the longest diagonal pattern.
Example:

Input:

[[2, 0, 2, 2, 2],
[2, 2, 2, 2, 2],
[2, 2, 2, 1, 2],
[2, 2, 2, 2, 2]]
Output:

3
Explanation: The pattern appears twice, once with length 3 and once with length 2. The maximum length is 3.

Constraints:

Maximum number of rows and columns in the matrix is 1000.
Example
Input
[[2, 0, 2, 2, 2], [2, 2, 2, 2, 2], [2, 2, 2, 1, 2], [2, 2, 2, 2, 2]]