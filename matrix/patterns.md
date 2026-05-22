# Matrix Patterns

## 1. Traversal Patterns
- Spiral order: maintain 4 boundaries (top, bottom, left, right), shrink after each direction
- Diagonal traversal: group by (i+j) for anti-diagonals, (i-j) for diagonals
- Rotate 90°: transpose + reverse each row
- Use: spiral matrix, rotate image, diagonal traverse

## 2. Search in Sorted Matrix
- Row-sorted + col-sorted: staircase from top-right — O(m+n)
- Fully sorted (row-major): treat as 1D, binary search — O(log(m*n))
- Use: search 2D matrix I/II, kth smallest in sorted matrix

## 3. DP on Grid
- dp[i][j] from dp[i-1][j], dp[i][j-1], dp[i-1][j-1]
- Use: unique paths, minimum path sum, maximal square, longest increasing path

## 4. BFS/DFS on Grid
- 4-directional or 8-directional movement
- Mark visited (in-place or with separate set)
- Multi-source BFS: enqueue all sources initially
- Use: number of islands, shortest path in binary matrix, walls and gates, rotten oranges

## 5. Prefix Sum 2D
- pre[i][j] = sum of rectangle [0,0] to [i-1,j-1]
- Query sum of [r1,c1] to [r2,c2]: inclusion-exclusion on 4 corners
- Use: range sum query 2D, maximal sum rectangle, count submatrices with all ones

## 6. Matrix Exponentiation
- Solve linear recurrences in O(k^3 log n)
- Build k×k transition matrix, raise to power n
- Use: Fibonacci in O(log n), count paths of length n, tiling problems

## 7. Largest Rectangle / Maximal Square
- Histogram approach: treat each row as base of histogram, use monotone stack
- Maximal square: dp[i][j] = min(left, top, top-left) + 1
- Use: maximal rectangle, maximal square, count square submatrices
