Task: Memory Management
You are given an integer array memory representing the memory state, with its length being a multiple of 8. Every set of 8 elements represents a memory unit where 1 means occupied and 0 means free.

You're also given a list of commands, where each command is in the format [action, value]. action is 1 for allocation and 0 for erasing. When action is 1, value is the number of memory units required; when action is 0, value is the ID of the memory unit to be erased.

Implement a memory management functionality:

For an allocation, locate contiguous free memory units in the array, and return the starting index of the allocation. Return -1 if allocation fails.
For an erasing operation, erase the memory unit by its ID and return 1. Return -1 if the ID does not exist.
Note that each memory unit begins allocation at index 0, then 8, then 16, and so on.

Example Test Cases:

memory = [0] * 16
commands = [[1, 2], [1, 3], [0, 1], [1, 4]]
Output:

[0, -1, 1, 8]
The memory array memory after processing these commands should be updated as:

[0, 2]
Example
Input
[0] * 16
[[1, 2], [1, 3], [0, 1], [1, 4]]