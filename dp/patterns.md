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
- Dominance-order variant: when item `a` can follow `b` only if multiple dimensions satisfy `b[k] <= a[k]` for all `k`, first sort dimensions inside each item, then sort the full item list lexicographically, then run LIS / weighted LIS on index order
- Why full sort matters: pairwise fit is only a partial order, so using LIS without globally sorting the items can miss valid chains; sorting linearizes the candidates so `dp[i]` only needs to look left
- Weighted version: if each valid extension contributes weight/height/value of the current item, use `dp[i] = weight[i] + max(dp[j])` over all compatible `j < i`
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

## 14. Sorted Assignment DP (Items → Bins with Capacity)
- Two sorted sequences (items & bins), each bin has limited capacity
- Sort both by position → optimal assignments never cross
- State: dp[item_idx][bin_idx][served] = min cost to assign remaining items using remaining bins, where current bin already served `served` items
- Decisions: skip bin (reset served) OR assign item to current bin (if capacity allows)
- The "served" dimension tracks capacity usage of current bin, resets when moving to next bin
- When greedy fails on assignment → think this pattern
- Use: LC 2463 (min total distance traveled), LC 1478 (allocate mailboxes), LC 2172 (max AND sum of array)

## 15. Partition Range-Sum → Buy/Sell Stock Reduction
- Problem: partition array into at most k subarrays, maximize sum of (max - min) per subarray
- Key insight: max-min of a subarray = (sell at max) - (buy at min), same as stock profit
- Each partition contributes one "transaction" → at most k transactions = Buy Sell Stock IV
- States: dp[K][state] where state ∈ {idle, bought, short-sold}
  - idle: can start a new buy or short-sell
  - bought (holding min): waiting to sell at max → profit = sell - buy
  - short-sold (holding max): waiting to buy back at min → profit = sell - buy
- For cyclic arrays: fix the global max at leftmost or rightmost of its subarray, linearize, run DP on both
- Space trick: if dp[i][K] depends on dp[i+1][K-1], reverse K's loop direction to avoid overwriting needed values

Use: LC 3743 (maximize cyclic partition score), LC 188 (buy sell stock IV)

## 16. Reduce to Knapsack/Coin-Change via Hidden Capacity
- Problem: assign items with a cost and a "coverage" value, minimize cost to cover capacity n
- Key insight: if picking item i gives time[i] "free" units, total coverage = time[i]+1 (item itself + free ones)
- Reframe as: items with weight = time[i]+1, value = cost[i], capacity = n → 0/1 knapsack (minimize cost to fill capacity)
- 1D space-optimized: iterate j from n down to 1, dp[j] = min(dp[j], cost[i] + dp[max(0, j-time[i]-1)])
- Base case gotcha for 2D version: dp[0][j] = cost[0] for ALL j from 1 to min(n, time[0]+1), not just j=time[0]+1
  (one item can cover any amount ≤ its full coverage)
- Use: LC 2742 (painting the walls)

## Key Gotchas
- Define states precisely — what does dp[i] represent? What are the transitions?
- Overlapping subproblems? If not, it's just recursion (no memoization needed)
- Check if greedy works first — dp is often overkill
- Space: can you roll the array? (e.g., 2D → 1D by processing row by row)
- **2D → 1D base case**: when collapsing to 1D, the inner loop naturally handles all reachable states from item 0. In 2D, you must manually set ALL cells reachable from the first item, not just the maximum one
