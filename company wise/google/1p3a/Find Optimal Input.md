Given that a microwave takes key stroke inputs and a target cooking time, find the optimal input considering the following costs for input:

Input 999 will be interpreted as 9 minutes 99 seconds.
Input 81 as 81 seconds.
Input 1221 as 12 minutes 21 seconds.
The cost of each key stroke is 1, and the cost of moving the finger to a different key is 2. For example, input 999 has a cost of 3, input 1122 has a cost of 6, and input 1234 has a cost of 10.

The input has to be within 10% of the target time. If the cost is the same, select the input that's closest to the target time.

For example, for a target time of 10 minutes, 888 is the optimal input (not 999).

Function Description

Complete the function findOptimalInput in the editor.

findOptimalInput has the following parameter:

targetTime: the target cooking time in seconds
Returns

int: the optimal input value

Constraints: :)

Example
Input
targetTime = 600
Output
888