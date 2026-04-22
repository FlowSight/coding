As an engineer in Amazon's Data Infrastructure Team, you are tasked with optimizing how information flows through its network of nodes. You are given n processing nodes, and the bandwidth capability of each node is given in an integer array named bandwidth.

There are streamCount data channels that need to be connected to two processing nodes, one as the main connection and the other as the secondary.

Each data channel must utilize a unique pair of nodes for its connections.

The dataFlow for each data channel is defined as the sum of the bandwidth of its main and secondary nodes:

dataFlow = bandwidth[main] + bandwidth[secondary]

Given an integer array bandwidth and an integer streamCount, find the maximum total dataFlow that can be achieved by optimally selecting unique pairs of connections for each data channel.

Input: An integer array bandwidth representing the bandwidth capacity of each node. An integer streamCount representing the number of channels.

Output:

The maximum total dataFlow that can be achieved.
Example:

Input: bandwidth = [1, 2, 3], streamCount = 2
Output: 8
Explanation: An optimal connection can be primary=[2,3], secondary=[1,3], which leads to a total dataFlow of (2+3) + (1+3) = 8.
Constraints:

2 <= n <= 1000
0 <= bandwidth[i] <= 10000
1 <= streamCount <= min(500, n*(n+1)/2)
Example
Input
1 2 3
2