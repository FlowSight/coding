Design a class to handle operations on a matrix. The class should include two methods: one to modify the matrix, and another to calculate the number of islands. Islands are formed by adjacent land cells (value 1) in horizontal or vertical directions. Initialization and modification of the matrix should be part of the methods. Implement and consider the response measures when there are numerous requests to modify the matrix.

How would you optimize the matrix modification and number of islands calculation for a large number of requests? Describe the design considerations and implementation details.

Example
Input
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1
modify 0 2 1
modify 2 0 1
count
modify 0 0 0
count