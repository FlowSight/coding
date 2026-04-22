AWS provides scalable systems. A set of n servers is used for horizontally scaling an application. The goal is to have the computational power of the servers in non-decreasing order. To achieve this, you can increase the computational power of each server in any contiguous segment by x. Choose the values of x such that after the computational powers are in non-decreasing order, the sum of the x values is minimum.

Example: There are n = 5 servers and their computational power is [3, 4, 1, 6, 2]. By adding 3 units to the subarray (2, 4) and 4 units to the subarray (4, 4), the final arrangement of the servers is [3, 4, 4, 9, 9]. The answer is 3 + 4 = 7.

Complete the function findMinimumSum in the editor below.

findMinimumSum has the following parameters:

• int power[n]: the computational powers of n different servers

Return: int: the minimum possible sum of integers required to make the array non-decreasing

Example
Input
5
3 4 1 6 2