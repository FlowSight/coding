A server network is represented as a tree of g_nodes servers indexed from 1 to g_nodes and g_nodes - 1 edges where the ith edges connect the servers g_from[i] and g_to[i]. The transfer time between any two connected servers is 1 unit.

Given the graph g, find the maximum time taken to transfer the data between any two servers in the system.

Function Description

Complete the function maximumTimeRequiredToTransferData in the editor.

maximumTimeRequiredToTransferData has the following parameters:

int g_nodes: the number of servers
int[] g_from: an array of integers representing the starting server of each edge
int[] g_to: an array of integers representing the ending server of each edge
Returns

int: the maximum time required to transfer data between any two servers

Example
Input
g_nodes = 3
g_from = [1, 2]
g_to = [2, 3]
Output
2