mplement an iterator that merges favorites and photos lists (yielding favorites first), while filtering out blocked IDs and ensuring no duplicates.

You will be given two input lists: one is the favorites, and the other is photos. You will also receive a set of blocked_ids that indicates the IDs to be blocked.

Your task is to create an iterator that first iterates over all elements in favorites that are not in blocked_ids, then iterates over all remaining elements in photos that are not in blocked_ids, ensuring that each element returned is unique.

Example:

favorites = [1, 2, 3]
photos = [2, 3, 4, 5]
blocked_ids = {2}
Output: [1, 3, 4, 5]

Example
Input
2
1 2 3
4
2 3 4 5
1
2