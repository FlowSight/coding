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
- Use when the answer is a numeric threshold (distance, time, speed, capacity, workload, cost), not necessarily an element in the input.
- Strong wording clues: **minimize the maximum**, **maximize the minimum**, minimum capacity/speed/time required, or largest feasible distance.
- Convert optimization into a decision problem: instead of constructing the optimal solution, guess `X` and ask, "Can the requirement be satisfied with answer at most/at least `X`?"
- Define a monotonic feasibility predicate:
  - Minimum feasible value: `false false false | true true true`; find the first `true`.
  - Maximum feasible value: `true true true | false false false`; find the last `true`.
- Prove monotonicity before coding. If `X` works, either every larger `X` must work or every smaller `X` must work.
- Set `lo` and `hi` to guaranteed bounds on the answer, then use the feasibility check to discard half of the answer space.
- A common clue is an expensive simulation that performs `k` operations. Ask whether a candidate `X` lets you count all required operations directly in one pass.
- Example: minimize maximum gas-station distance. Guess distance `D`; a gap `g` needs `ceil(g / D) - 1` new stations. If the total is at most `k`, `D` is feasible, and every larger distance is also feasible.
- Recognition checklist:
  1. Is the required answer a number?
  2. Can I guess that number and efficiently check feasibility?
  3. Are the feasibility results monotonic?
  4. Can I establish safe minimum and maximum bounds?
- Use: koko eating bananas, split array largest sum, capacity to ship packages, magnetic force, minimize max distance to gas station

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
- always do if(l+1==r) check
