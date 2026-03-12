Given an n x n matrix where some positions are filled with various characters, implement a function to rotate the matrix and simulate a gravity effect. The gravity will cause elements to fall to the bottom until blocked by either the floor or another element. Positions without elements are represented by '.'. A barrier is defined which will block elements from falling. Input is a 2D character array and output is the rotated matrix with applied gravity.

Input Format:

The first line contains an integer n, the size of the matrix.
The next n lines contain n characters each, representing the matrix content.
Output Format:

Output n lines representing the matrix after rotation and gravity effects.
Example:

Input:

3
#..
.a.
...
Output:

...
.a.
.#.
Note: Assume the maximum value of n is 100.

Example
Input
3
#..
.a.
...