Problem: Earliest User Who Logged In Exactly Once (OOD / Data-Structure Design)
You are given a stream/list of user login events. Each event contains:

user_id: string or integer
login_time: integer timestamp (e.g., seconds)
Design a data structure/class that supports:

add_login(user_id, login_time): add a login event
query(): return the user whose total login count is exactly 1 and whose login_time is the earliest among such users.
If no such user exists, return null (or empty / -1, define your convention).

Requirements
Provide and implement the core data structure design.
Analyze time and space complexity.
Constraints (can be clarified during interview)
Number of events N up to around 1e5
Number of distinct users up to around 1e5
login_time is a non-negative integer
Example Tests
Input:

add: (A, 10), (B, 5), (A, 11), (C, 7)
query() Output: B
Input:

add: (A, 10), (A, 9)
query() Output: null
Input:

add: (A, 10), (B, 10)
query() Output: A or B (depending on your tie-break rule)
Example
Input
add A 10
add B 5
add A 11
add C 7
query
Output
B