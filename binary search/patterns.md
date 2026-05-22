# Binary Search Patterns

## 1. Standard Binary Search
- Search for exact value in sorted array
- lo=0, hi=n-1, mid=(lo+hi)/2
- Return index or -1

## 2. Lower/Upper Bound
- Lower bound: first index where a[i] >= target
- Upper bound: first index where a[i] > target
- Use: count occurrences = upper_bound - lower_bound, insert position

## 3. Binary Search on Answer
- "What's the minimum X such that condition(X) is true?"
- Monotonic feasibility: if X works, X+1 also works (or vice versa)
- lo = min possible, hi = max possible; binary search on X, check feasibility
- Use: koko eating bananas, split array largest sum, capacity to ship packages, magnetic force

## 4. Search in Rotated Array
- One half is always sorted — determine which, then decide direction
- With duplicates: worst case O(n) when lo==mid==hi, shrink boundaries
- Use: search in rotated sorted array I/II, find minimum in rotated array

## 5. Peak Finding
- If a[mid] < a[mid+1]: peak is to the right → lo = mid+1
- Else: peak is at mid or left → hi = mid
- Use: find peak element, mountain array problems

## 6. Binary Search on Real Numbers
- For floating point: iterate fixed number of times (e.g., 100) instead of while(lo < hi)
- Or use eps-based: while(hi - lo > 1e-9)
- Use: sqrt, median of two sorted arrays, minimize max distance

## 7. 2D Binary Search
- Search in row-sorted and column-sorted matrix
- Staircase: start top-right or bottom-left, eliminate row/col each step — O(m+n)
- Use: search 2D matrix, kth smallest in sorted matrix

## Key Gotchas
- **Off-by-one**: choose lo=mid+1 or hi=mid (not mid-1) carefully based on what's being searched
- **Loop termination**: lo < hi (converges to answer) vs lo <= hi (searches exact)
- **Overflow**: mid = lo + (hi-lo)/2, not (lo+hi)/2
- Identify monotonic property first — if no monotonicity, binary search won't work
