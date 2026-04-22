In a cloud system, there are n servers where the memory capacity of the ith server is represented by the array memory[i]. The system always contains an even number of servers. If the system has 2x servers, x of them will be primary servers and the other x will be backup servers. For each primary server P, there exists a backup server B where the memory capacity B ≥ memory capacity P. The system's memory capacity is the sum of the memory capacity of all the primary servers.

Given n servers and an array memory, find the maximum system memory capacity that can be formed using the n servers.

Example
Given 5 servers and memory = [2, 4, 3, 1, 2].

Primary Servers | Backup Servers | Conditions --- | --- | --- serverA, serverB | serverC, serverD | memory[serverA] ≤ memory[serverC], memory[serverB] ≤ memory[serverD] serverA, serverD | serverB, serverE | memory[serverA] ≤ memory[serverB], memory[serverD] ≤ memory[serverE] serverA, serverC | serverE, serverB | memory[serverA] ≤ memory[serverE], memory[serverC] ≤ memory[serverB]

In the second configuration, the system memory capacity is memory[serverA] + memory[serverD] = 3. While in the third configuration, it is memory[serverA] + memory[serverC] = 5.

Example
Input
5
2 4 3 1 2