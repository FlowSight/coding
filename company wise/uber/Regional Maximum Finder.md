You are given a 2D array. Your task is to find the regional maxima in the array and return a 2D array of size (X * 2) where each row contains the position [i, j] of a regional maximum.

Definition of Regional Maximum:

A cell (i, j) is considered a regional maximum if:

array[i][j] != 0
array[i][j] is the maximum value within its region.
Definition of Region:

For a cell (i, j) with value cell:

The region is defined as the rectangular area (i - cell to i + cell) * (j - cell to j + cell).
Exclude the corner cells from above: (i - cell, j - cell), (i - cell, j + cell), (i + cell, j - cell) and (i + cell, j + cell).
If the calculated region goes out of bounds, ignore those out-of-bound cells.
Function Description

Complete the function findRegionalMaxima in the editor.

findRegionalMaxima has the following parameter:

int[][] array: a 2D array of integers
Returns

int[][]: a 2D array where each row contains the position [i, j] of a regional maximum

Constraints: :)

Example
Input
array = [[3, 0, 1], [2, 0, 0], [0, 0, 0]]
Output
[[0, 0], [0, 2]]