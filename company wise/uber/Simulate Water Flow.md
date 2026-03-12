**See the Image Source section at the very bottom of the page for the original problem statement **

Civil engineers are using a digital elevation model to simulate how rainfall flows over terrain, represented as a 2D grid of integers where each number indicates the elevation at that point. The water starts flowing from a specific location, given by two coordinates (startRow, startCol), and moves to neighboring cells—up, down, left, or right—if the next cell's height is less than or equal to the current one. The water continues flowing until it can no longer move to any lower or equal elevation. Your task is to track this process by returning a new 2D grid, where each cell shows the time step when it first becomes wet, starting from 0 at the water's initial point. If a cell never gets wet, mark it as -1. The challenge is to design an efficient solution that works within a reasonable time limit, as water flow simulations can involve large terrain grids.

** Thanks to Charlotte baby **

Constraints: ``

Example
Input
heights = [[3, 2, 1], [6, 5, 4], [9, 8, 7]]
startRow = 1
startCol = 1
Output
[[-1, 1, 2], [-1, 0, 1], [-1, -1, -1]]