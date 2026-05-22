# Backtracking Patterns

## 1. Subsets / Power Set
- Include or exclude each element → 2^n subsets
- Iterate index forward to avoid duplicates
- For duplicates in input: sort first, skip same element at same level
- Use: subsets, subsets II, power set

## 2. Permutations
- Swap-based: swap(i, j) for j in [i..n-1], recurse on i+1
- Used-array based: track which elements are placed
- For duplicates: sort + skip if same char used at same position
- Use: permutations, permutations II, next permutation

## 3. Combinations / Combination Sum
- Choose r from n: recurse with (index+1, remaining-1)
- Combination sum (reuse allowed): recurse with same index
- Combination sum (no reuse): recurse with index+1
- Prune: if current sum > target, stop early
- Use: combination sum I/II/III/IV, phone letter combinations

## 4. Constraint Satisfaction (Board Problems)
- Place element, check validity, recurse, undo
- Constraint checking: row/col/box for Sudoku, row/col/diag for N-Queens
- Use: N-Queens, Sudoku solver, crossword puzzle

## 5. Palindrome Partitioning
- At each position, try all valid palindromic prefixes, recurse on remainder
- Precompute palindrome checks (dp[i][j]) for O(1) lookup
- Use: palindrome partitioning, word break II

## 6. Path Finding / Grid Backtracking
- Move in 4/8 directions, mark visited, unmark on backtrack
- Use: word search, unique paths III, rat in a maze

## Key Gotchas
- Always think about pruning — it's the difference between TLE and AC
- Sort input to enable duplicate skipping and early termination
- Backtrack = undo state changes after recursive call returns
- If order doesn't matter, always move forward (start from index) to avoid duplicates
