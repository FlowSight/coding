Another question about defusing bombs - uber-find-minimum-time-to-defuse-all-bombs

Janet is faced with the task of defusing N bombs, numbered from 1 to N. Each bomb i has a timer and will detonate in Yi seconds. To neutralize bomb i, Janet needs Xi seconds. He must finish defusing each bomb before or exactly when its timer runs out. Importantly, he can only work on one bomb at a time. Knowing this in advance, Janet has asked for your assistance. Your goal is to determine whether it's possible for him to defuse all the bombs in time. If it is, return the minimum total time required to complete the defusals. Otherwise, return -1.

Function Description

Complete the function defuseBombs in the editor.

defuseBombs has the following parameter:

int[][] bombInfo: an array of int arrays where each subarray contains two elements [Xi, Yi], representing the time taken by Janet to defuse the ith bomb and the time by which the ith bomb will explode
Returns

int: the minimum total time required to defuse all bombs if possible, otherwise -1

Example
Input
bombInfo = [[2, 4], [1, 9], [1, 8], [4, 9], [3, 12]]
Output
11