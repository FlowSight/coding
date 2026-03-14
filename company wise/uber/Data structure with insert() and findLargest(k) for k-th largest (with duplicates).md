Problem
Design and implement a data structure that supports:

insert(num: int) -> None: Insert an integer into the structure (duplicates allowed).
findLargest(k: int) -> int: Return the k-th element in the list sorted in descending order (0-indexed).
Example:

insert(3)
insert(3)
insert(2)
findLargest(0) -> 3
findLargest(1) -> 3
findLargest(2) -> 2
Requirement: Make findLargest(k) as efficient as possible.

Constraints
Number of operations: 1 <= Q <= 2 * 10^5
num range: -10^9 <= num <= 10^9
Queries are valid: for every findLargest(k), 0 <= k < current_size
Task
Explain your design and implement the two methods.

Example
Input
insert 3
insert 3
insert 2
findLargest 0
findLargest 1
findLargest 2
Output
3
3
2
