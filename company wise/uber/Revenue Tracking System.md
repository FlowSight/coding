Design a system to track revenues. Implement the following functions:

add(revenue: int) -> int: Add a new revenue and return a new revenue ID.
add(revenue: int, id: int): Add new revenue to the existing revenue with the given ID.
showRevenue(id: int) -> int: Return the total revenue for the given ID.
Functions should support dynamic input and multiple calls. Assume the system starts with no revenue records. The system should be time-efficient.

Example:

add(10) -> 1
add(20) -> 2
add(30, 1) -> null
showRevenue(1) -> 40
showRevenue(2) -> 20
Constraints:

Each call to add and showRevenue should be as quick as possible.
revenue is an integer in the range [-10^9, 10^9].
ID is unique and globally incrementing.
Example
Input
add 10
add 20
add 30 1
showRevenue 1
showRevenue 2