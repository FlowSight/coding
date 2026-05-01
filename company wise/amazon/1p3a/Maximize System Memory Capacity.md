Amazon's developers are working on optimizing their cloud system's capacity. In the system, there are n servers where the memory capacity of the i-th server is represented by the array memory[i]. The system always contains an even number of servers. If the system has 2x servers, then x of them will be primary servers and the other x will be backup servers. For each primary server P, there exists a backup server B such that: memory[B] >= memory[P]. The system memory capacity is the sum of the memory capacities of all primary servers. Your task is to determine the maximum possible system memory capacity that can be formed using the given n servers.

Input:

An integer array memory representing the memory capacity of each server. Output:
The maximum possible system memory capacity.
Example:

Input: memory = [1, 2, 3, 4]
Output: 3
Explanation: An optimal server allocation is primary=[1,2], backup=[3,4], which provides a total primary server memory capacity of 1+2=3. 
- Primary 1 is supported by backup 3 (3>=1) ✓
- Primary 2 is supported by backup 4 (4>=2) ✓
Constraints:

1 <= n <= 10000
memory[i] represents the memory capacity of each server, 1 <= memory[i] <= 10000. There are always an even number of servers in the system.
Example
Input
1 2 3 4