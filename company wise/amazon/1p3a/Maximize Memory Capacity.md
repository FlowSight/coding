Amazon developers are working on optimizing the capacity of their cloud system. In this system, there are n servers, where the memory capacity of the i-th server is represented by the array memory[i]. A system always contains an even number of servers. If the system has 2x servers, then x will be primary servers and the other x will be backup servers. For each primary server P, there exists a backup server B where: memory[B] >= memory[P].

The system's memory capacity is the sum of the memory capacities of all primary servers.

Given n servers and an array memory, find the maximum system memory capacity that can be formed using the n servers.

Complete the function maximumCapacity in the editor below.

Return: long int: the maximum system memory capacity.

Constraints: 2 <= n <= 2*10^5

Example
Input
4
2 2 3 4