You have two jugs with different capacities and a target capacity. Initially, both jugs are empty. You can perform the following operations:

Fill one jug completely.
Empty one jug.
Pour water from one jug to the other until the former is empty or the latter is full.
The goal is to determine the minimum number of operations required to reach the target capacity and output the sequence of operations.

Example: For two jugs with capacities [3, 5] and a target capacity of 4, a possible sequence is:

(0, 0) -> (0, 5)
(0, 5) -> (3, 2)
(3, 2) -> (0, 2)
(0, 2) -> (2, 0)
(2, 0) -> (2, 5)
(2, 5) -> (3, 4) -> target reached.
Example
Input
jug1 = 3
jug2 = 5
target = 4