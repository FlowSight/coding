# HashMap / TreeMap Patterns

## 1. Frequency Count
- Count occurrences, check conditions on frequencies
- Use: valid anagram, top K frequent elements, group anagrams, majority element

## 2. Two-Sum Pattern
- Store complement in map as you iterate
- Generalize: subarray sum = K via prefix sum + map of (prefix_sum → count)
- Use: two sum, subarray sum equals K, continuous subarray sum, count nice subarrays

## 3. Sliding Window + HashMap
- Track window character frequencies in a map
- Shrink window when constraint violated
- Use: minimum window substring, longest substring with at most K distinct chars, permutation in string

## 4. Index Tracking
- Map value → last/first index seen
- Use: contains duplicate II (within distance K), longest consecutive sequence, first unique character

## 5. Ordered Map (TreeMap / std::map)
- Maintain sorted keys with O(log n) insert/search/delete
- lower_bound / upper_bound for range queries
- Use: my calendar, count of smaller numbers after self, skyline problem

### Dynamic Interval Set
- Store disjoint canonical intervals as `map<start,end>`. Before inserting `[L,R]`, use `lower_bound(L)` and inspect its predecessor because an interval starting before `L` may overlap or touch the new range.
- Decide the boundary convention first:
  - Half-open intervals `[L,R)` merge when `nextStart <= mergedRight`.
  - Inclusive unit-segment intervals `[L,R]` merge when `nextStart <= mergedRight + 1`.
- During the forward scan, continuously extend `mergedRight = max(mergedRight, intervalEnd)`. A larger right boundary can trigger additional merges, so the loop condition must use the updated boundary.
- Chain-merge example for inclusive ranges: existing `[10,15]`, `[18,25]`, insert `[16,22]` -> merge to `[10,22]` -> then merge to `[10,25]`.
- Delete every absorbed interval, then insert exactly one canonical merged interval. Keeping touching intervals separate can make a query spanning their boundary incorrectly return false.
- To find the interval that may contain `x`, use `upper_bound(x)` and step back once; this gives the interval with the largest start `<= x`. Guard against `begin()` before decrementing.
- For removal `[L,R]`, merge is not needed: erase every overlapping interval and reinsert at most two leftovers, `[oldStart,L-1]` and `[R+1,oldEnd]` for inclusive ranges.
- Use: LC 715 Range Module, interval calendars, dynamic covered-range queries.

## 6. Design Problems
- LRU Cache: hashmap + doubly linked list
- LFU Cache: hashmap + frequency buckets
- Time-based key-value store: map of key → sorted list of (timestamp, value)
- Use: LRU cache, LFU cache, snapshot array, time map

## Key Gotchas
- unordered_map O(1) average but O(n) worst case — use custom hash to avoid hash collision attacks
- For multi-set operations: map<val, count> is often cleaner than multiset
- Prefix sum + hashmap: initialize map with {0: 1} for subarrays starting at index 0
- Map iterators returned by `find`, `lower_bound`, or `upper_bound` use `->` for entry members: `it->first` and `it->second` (equivalent to `(*it).first` and `(*it).second`), not `it.first` or `it.second`
