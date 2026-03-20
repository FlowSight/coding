The organizers of a gaming tournament want to analyze player participation based on event logs. There are n event logs, where arr[i] indicates the playerId of the player who participated in the ith event. The organizers need to identify subarrays of these logs that are consistent, meaning that the frequency of the most frequent player in the subarray matches the frequency of the least frequent player in the entire array. Determine the maximum length of such consistent logs.

Function Description

Complete the function findConsistentLogs with the following parameters:

int arr[n]: the playerIds present in the event logs

Returns

int: the maximum length of the consistent logs

Constraints: 1 ≤ n ≤ 104

Example
Input
arr = [1, 2, 1, 3, 4, 2, 4, 3, 3, 4]
Output
8