# Array Patterns

## 1. Two Pointers
- Opposite ends: sorted pair sum, container with most water, valid palindrome
- Same direction: remove duplicates, move zeroes, slow/fast pointer
- Use: O(n) after sorting, or on already sorted input

## 2. Sliding Window
- Fixed size: max sum of subarray of size k
- Variable size: expand right until invalid, shrink left until valid
- Track window state with hash map or frequency array
- Use: longest substring without repeating, minimum window substring, max consecutive ones III

## 3. Prefix Sum / Difference Array
- prefix[i] = sum(a[0..i-1]) → range sum in O(1)
- Difference array: d[l] += val, d[r+1] -= val → range updates in O(1), reconstruct with prefix sum
- 2D prefix sum for submatrix queries
- Use: subarray sum equals K (prefix + hashmap), range addition, count subarrays with sum in range

## 4. Kadane's Algorithm
- Max subarray sum: dp[i] = max(a[i], dp[i-1] + a[i])
- Variants: max circular subarray (total - min_subarray), max product subarray (track min and max)
- Use: maximum subarray, maximum product subarray

## 5. Sorting + Custom Comparators
- Sort then scan: merge intervals, meeting rooms, largest number
- Custom sort: comparator based on problem's ordering
- Use: merge intervals, non-overlapping intervals, reorder data in log files

## 6. Binary Search on Array
- Search in sorted/rotated array, find first/last occurrence
- Binary search on answer: "can we achieve X?" → check feasibility
- Use: search in rotated array, find peak, koko eating bananas, capacity to ship

## 7. Monotone Stack
- Find next/prev greater/smaller element in O(n)
- Stack/deque stores indices; pop when current violates monotonicity
    - pop from where if queue? if we are pushing in back,(b...f),back-to-front is monotonic
- Use: daily temperatures, largest rectangle in histogram, trapping rain water

## 8. Partitioning / Dutch National Flag
- 3-way partition: lo, mid, hi pointers
- QuickSelect for kth element in O(n) average
- Use: sort colors, wiggle sort, kth largest element

## 9. Cyclic Sort
- Place each number at its "correct" index
- Use: find missing number, find duplicate, first missing positive

## 10. Merge Intervals Pattern
- Sort by start, merge overlapping
- Use: insert interval, meeting rooms, interval list intersections

## 11. Merge 2 arrays into sorted array (incre or decresing)
- if arr is sorted, start from end, keep merging in place
- if not sorted, for any collision (arr1[i] == arr2[j]) detect rest to find which one is greater (O(n^2))

## 12. 3 pointer (0<i<j<k<n)
- iterate over j  , calculate with 0..j-1 and j+1..n-1 OR
    move (j/k) pair..o(n^2)..but create search space in i..to search for (j,k) combo
- LC 2179

## 13. BIT (Fenwick Tree)
- 1-indexed array; node i covers range [i - (i&-i) + 1, i]
- Point update + prefix query in O(log n)
- i & (-i) = lowest set bit → update goes up (i += i&-i), query goes down (i -= i&-i)
- Use: range sum with updates, count inversions, count smaller elements after self, 2D BIT for submatrix