// Given a list of servers, each server has a cost associated with it. The servers are represented as an array of N integers.
// If you choose server i, then i servers ahead of it are automatically selected.
// You may skip selecting those servers, but sometimes it might be beneficial to select them as well.
// Find the min cost to cover all servers.

dp[i] = cost to select i to n-1 servers
     = cost[i] + min of (dp[i+1] to dp[min(i+i,n-1)])