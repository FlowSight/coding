A 2-D grid consisting of some blocked (represented as '#') and some unblocked (represented as '.') cells is given. The starting position of a pointer is in the top-left corner of the grid. It is guaranteed that the starting position is in an unblocked cell, and it is also guaranteed that the bottom-right cell is unblocked. Each cell of the grid is connected with its right, left, top, and bottom cells (if those cells exist). It takes 1 second for a pointer to move from a cell to its adjacent cell. If the pointer can reach the bottom-right corner of the grid within maxTime seconds, return the string 'Yes'. Otherwise, return the string 'No'.

Function Description

Complete the function reachTheEnd in the editor.

reachTheEnd has the following parameter(s):

String[] grid: an array of strings representing the rows of the grid
int maxTime: the maximum time to complete the journey
Constraints:

1 <= rows <= 500
1 <= maxTime <= 10^5
Example
Input
grid = ["..#", "#.##", "#..."]
maxTime = 5
Output
"Yes"