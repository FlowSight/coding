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

## 6. Design Problems
- LRU Cache: hashmap + doubly linked list
- LFU Cache: hashmap + frequency buckets
- Time-based key-value store: map of key → sorted list of (timestamp, value)
- Use: LRU cache, LFU cache, snapshot array, time map

## Key Gotchas
- unordered_map O(1) average but O(n) worst case — use custom hash to avoid hash collision attacks
- For multi-set operations: map<val, count> is often cleaner than multiset
- Prefix sum + hashmap: initialize map with {0: 1} for subarrays starting at index 0
