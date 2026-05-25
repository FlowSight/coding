# DP Patterns

## 1. Linear DP
- dp[i] depends on dp[i-1], dp[i-2], etc.
- Examples: Fibonacci, climbing stairs, house robber, decode ways
- Space optimization: often only need last 1-2 states

## 2. Knapsack
- 0/1 Knapsack: dp[i][w] = max value using first i items with capacity w
- Unbounded: inner loop forward (item reusable)
- Bounded: binary lifting or monotone deque optimization
- Subset sum is a special case (value = weight)
- Use: coin change, partition equal subset sum, target sum

## 3. Interval DP
- dp[i][j] = optimal for subarray/substring [i..j]
- Recurrence: try all split points k in [i..j-1]
- Fill diagonally (by length) or bottom-up
- Use: matrix chain multiplication, burst balloons, palindrome partitioning, stone game

## 4. LIS / LCS
- LIS: O(n log n) with patience sorting (binary search on tails array)
- LCS: O(n*m) table, reconstruct by backtracking
- Edit distance: insert/delete/replace variants of LCS
- Use: longest increasing subsequence, diff algorithms

## 5. DP on Trees
- Root the tree, dp[node] computed from dp[children]
- Rerooting technique: compute for one root, then propagate O(n)
- Use: max path sum, tree diameter, count nodes in subtree conditions

## 6. Bitmask DP
- dp[mask] where mask ⊆ {0..n-1}, n ≤ 20
- Iterate subsets of mask: `for(s=mask; s; s=(s-1)&mask)`
- Use: TSP, assignment problem, Hamiltonian path, SOS DP

## 7. Digit DP
- Count numbers in [0..N] with some digit property
- State: (pos, tight, started, ...extra)
- Use: count numbers with digit sum = K, no repeated digits, divisible by M

## 8. DP on DAG / Topological Order
- Process nodes in topological sort order
- Longest/shortest path in DAG is O(V+E)
- Use: course schedule variants, job scheduling with dependencies

## 9. State Machine DP
- States represent "phases" (e.g., holding stock, cooldown, not holding)
- Transitions are edges between states per step
- Use: buy/sell stock with cooldown/fee, regex matching

## 10. SOS DP (Sum over Subsets)
- dp[mask] = sum of f[s] for all s ⊆ mask
- O(n * 2^n) — iterate each bit position
- Use: counting pairs with AND=0, max XOR subset, inclusion-exclusion on bitmasks

## 11. Convex Hull Trick / Li Chao Tree
- Optimize dp[i] = min(dp[j] + cost(j,i)) when cost has form a[j]*x[i] + b[j]
- Maintain set of lines, query minimum at point x
- Use: divide & conquer optimization, Knuth's optimization, linear recurrences with slope

## 12. Profile DP / State Compression on Narrow Grids
- Grid is narrow (few columns) but long (many rows)
- Enumerate all valid row configurations, group into equivalence classes by "type"
- dp[row][type] with transitions between types — reduces exponential states to constant
- Can also use bitmask to encode full row state when columns ≤ ~20
- Examples:
  - Paint n×3 grid (LC 1411): 12 valid rows → 2 types (ABC, ABA), O(1) transition per row
  - Domino/tromino tiling (LC 790): track which cells in current row are filled
  - Broken profile DP: bitmask of boundary between placed and unplaced cells
- Use: narrow grid coloring, tiling, placing non-attacking pieces on narrow board

## 13. Weighted Interval/Job Scheduling
- Sort intervals by end time
- dp[i] is inclusive of 0..i
- think of left-to-right and opposite
- Binary search for the last non-conflicting interval (rightmost with end < current start) (LC 1751), else you can keep the time points sorted and have a running dp on timestamps, then dp[starttime] we should look for 
- dp[i] = max value considering first i intervals
- Recurrence: dp[i] = max(dp[i-1], dp[bsIdx+1] + value[i]) — skip or take
- Complexity: O(n log n + nk) with precomputed binary search indices
- Use: LC 1235 (max profit job scheduling), LC 1751 (max events attended II), LC 435/452 variants

## Key Gotchas
- Define states precisely — what does dp[i] represent? What are the transitions?
- Overlapping subproblems? If not, it's just recursion (no memoization needed)
- Check if greedy works first — dp is often overkill
- Space: can you roll the array? (e.g., 2D → 1D by processing row by row)
