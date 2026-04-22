Problem: Design a Per-User Rate Limiter (Accept/Reject Requests)
Implement a per-user rate limiter RateLimiter that decides whether a new request at a given time should be accepted.

Method to implement:

allow(user_id, timestamp) -> bool
user_id: user identifier
timestamp: integer timestamp (e.g., seconds)
returns True if the request is accepted and recorded; otherwise returns False.
Rate limiting rule
Given parameters:

window_size: time window size (same unit as timestamp)
limit: maximum number of requests allowed per user in any window of length window_size
When a request arrives at time timestamp:

count how many historical requests from this user fall in (timestamp - window_size, timestamp]
if the count is < limit, accept and record it; otherwise reject
Requirements
Clearly describe the data structure design (e.g., queue/deque/hash map).
Analyze time and space complexity.
Assume allow is called frequently (up to ~1e5).
Constraints (suggested)
Total calls N up to 2e5
timestamp is non-decreasing (if not, explain how you would handle it)
Example
Let window_size=10, limit=3

allow(A, 1) -> True

allow(A, 2) -> True

allow(A, 3) -> True

allow(A, 4) -> False

allow(A, 12) -> True

allow(A, 1) -> True

allow(B, 1) -> True

allow(A, 2) -> True

Example
Input
10 3
A 1
A 2
A 3
A 4
Output
True
True
True
False