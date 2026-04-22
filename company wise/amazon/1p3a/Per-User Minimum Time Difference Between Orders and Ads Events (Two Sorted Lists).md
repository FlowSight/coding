You are given two lists sorted ascending by timestamp:

orders: user order events
ads: user ads-related events
Each event contains at least userId and an integer timestamp.

For each userId, find a pair of events (orderEvent, adEvent)—one from orders and one from ads for that same user—such that the absolute time difference |orderTimestamp - adTimestamp| is minimized. Return the minimum time difference for each user (optionally also the corresponding pair).

Constraints/notes:

Both input lists are globally sorted by timestamp (events of different users may be interleaved).
If a user appears in only one list, return no result for that user.
Assume:

len(orders), len(ads) up to 1e5
timestamp fits in 64-bit integer
Implement with the best possible time complexity.

Example
Input
orders = [(u1,1),(u1,10),(u2,5)]
ads    = [(u1,6),(u2,100)]
Output
u1 -> 4 (order 10, ad 6)
u2 -> 95 (order 5, ad 100)