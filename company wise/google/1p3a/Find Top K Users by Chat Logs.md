Given a set of chat log records, you need to find the top k users who send the most messages. Implement a function find_top_k_users(logs: List[str], k: int) -> List[str>, where logs is a list of strings representing user messages (e.g., "user_id message"), and k is the number of top users to query. Return the user_ids of the top k users. Assume the number of users and log length do not exceed $10^5$. Provide test cases.

Example
Input
10
a 1
b 1
a 2
c 1
a 1
b 2
d 4
a 1
d 3
b 1
3