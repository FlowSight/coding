Imagine you are an avid gardener planning the layout of a large garden. You have to generate a 2D grid where each cell represents a plot in the garden. You can either plant a flower in a plot or leave it empty. After planting, you want to analyze the garden to find unique arrangements of flowers that form an "L" shape, as these arrangements are aesthetically pleasing and optimize space usage.

A value of 1 in the grid indicates a plot where a flower is planted, and a value of 0 indicates an empty plot.

An "L" shaped flower arrangement is defined as follows:

A collection of 3 plots of a garden is said to be L shaped arrangement if one of its plots is in the same row with another plots and in the same column with the third plots. The 3 plots do not have to be next to each other. All three plots must contain flowers (value of 1).

Input: The inputs provided will include "row", "col", "magicNumber", and "mod". "Row" and "Col" specify the size of the grid in terms of rows and columns. To determine the presence of a flower in any cell, we use the formula:

((i+j*magicNumber)%mod)%2

where "i" and "j" refer to the row and column indices, respectively. The indices "i" and "j" start from 0 and go up to row-1 and col-1, respectively. The '%' symbol denotes the modulus operation.

Output: Return the number of such "L" shaped arrangements in the garden.

Constraints:

1 ≤ row ≤ 1000
1 ≤ col ≤ 1000
0 ≤ grid[i][j] ≤ 1
1 ≤ mod ≤ 1000000
1 ≤ magicNumber ≤ 1000000
Example
Input
row = 3
col = 3
magicNumber = 1
mod = 4
Output
4