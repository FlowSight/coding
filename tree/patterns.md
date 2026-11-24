# Tree Patterns

## 1. DFS Traversals
- Preorder (root, left, right): serialize tree, copy tree
- Inorder (left, root, right): BST gives sorted order
- Postorder (left, right, root): delete tree, evaluate expression
- Use: reconstruct from preorder+inorder, flatten to linked list

## 2. BFS / Level-Order
- Queue-based, process level by level
- Use: level order traversal, right side view, zigzag traversal, minimum depth

## 3. LCA (Lowest Common Ancestor)
- Binary lifting: O(n log n) preprocess, O(log n) query
- Euler tour + RMQ: O(n) preprocess, O(1) query
- Simple recursive: if both sides return non-null, current is LCA
- Use: distance between nodes, path queries

## 4. Tree DP
- dp[node] from dp[children] — bottom-up (postorder)
- Rerooting: compute dp for one root, propagate to all nodes in O(n)
- Use: diameter, max path sum, number of nodes in each subtree condition

## 5. Depth + Subtree-Height Decomposition
- Precompute `depth[node]` and `subtreeHeight[node]`
- Any best root-to-leaf path through `node` contributes `depth[node] + subtreeHeight[node]`
- For subtree-removal queries, answer using the best path that stays outside the removed subtree
- Common trick: group nodes by depth, keep the top 2 subtree heights at each depth
- Query rule: if removed node had the maximum height at its depth, fall back to second maximum; otherwise keep the maximum
- Use: LC 2458 (height of binary tree after subtree removal queries), exclude-subtree height queries

## 6. Binary Search Tree (BST)
- Inorder = sorted; search/insert/delete O(h)
- Validate: pass (min, max) range down
- Use: kth smallest, inorder successor, recover BST

## 7. Segment Tree
- Store an aggregate for an interval at each node; split `[l,r]` into `[l,mid]` and `[mid+1,r]`.
- Point update/range query is `O(log n)`; lazy propagation supports range update/range query in `O(log n)`.
- array value ranges are huge : just take array, do ops on index (coordinate compression)
- dont put actual hydrated array, use logical array, use left,right,mid

### Dynamic / Lazy Segment Tree State
- Define the node-state invariant before coding. For range coverage, two states are insufficient because "not fully covered" can mean either completely uncovered or partially covered. Use three states: `0 = uncovered`, `1 = mixed/partial`, `2 = fully covered`.
- **Half-open vs inclusive ranges**: if the API gives `[left,right)` but the tree stores inclusive leaf indices `[l,r]`, and leaf `i` represents `[i,i+1)`, convert the operation to `[left,right-1]`.
- **Push-down before a partial write**: a standalone new node starts uncovered, but children created by splitting a uniform parent must inherit that parent's covered/uncovered state. Otherwise, a partial removal from a fully covered node loses the untouched coverage.
- **Pull-up after a child write**: recompute the parent from both children. Equal uniform children collapse to their shared state; different states make the parent mixed.
- **Full overwrite invalidates descendants**: when an update fully covers or uncovers a node, old child state is stale. Discard the children or overwrite their states before any later partial update.
- A missing child is meaningful only together with the parent invariant. It may mean "unmaterialized because the parent is uniform," not necessarily "uncovered."
- Query a uniform node directly, even for a partial overlap. Descend only when the node is mixed.
- Use: LC 715 Range Module, dynamic interval coverage, range assignment.

### Coordinate-Compressed Segment Tree: Point vs Gap Leaves
- Before building the tree, decide what leaf `i` represents:
  - **Point leaf**: the compressed value `coords[i]`. Use for frequencies, counts, point values, and order statistics. With `m` coordinates, build indices `[0, m-1]` (e.g. LC 493 Reverse Pairs).
  - **Gap leaf**: the elementary half-open interval `[coords[i], coords[i+1])`. Use for covered distance, interval-union length, rectangle area, and perimeter. With `m` coordinates, there are `m-1` leaves, so build `[0, m-2]` (e.g. LC 850 Rectangle Area II).
- For gap leaves, a geometric interval `[coords[L], coords[R])` maps to tree indices `[L, R-1]`. The coordinate at `R` is the right boundary, not another covered gap.
- A gap-tree node covering leaf indices `[l,r]` represents `[coords[l], coords[r+1])`, so its full geometric length is `coords[r+1] - coords[l]`.
- Adjacent ranges such as `[5,7)` and `[7,9)` map to different leaves. Their shared endpoint has zero length, so it must not be counted as an overlap.
- For inclusive discrete ranges, convert length to an inclusive right endpoint: `[left, left+length-1]` (e.g. LC 699 Falling Squares). This `-1` has the same boundary-ownership purpose but is a different representation from compressed geometric gaps.

## 8. Segment Tree on Tree (HLD)
- Heavy-Light Decomposition: decompose into chains for path queries
- Each chain handled by segment tree — O(log^2 n) per query
- Use: path sum/max queries, subtree queries with updates

## 9. Trie (Prefix Tree)
- Each edge = character, node = prefix endpoint
- **Combined-key trie**: when a query has two string constraints, encode both in one path with a separator not present in the alphabet. For prefix + suffix search, query `suffix + '{' + prefix`.
- To support every `(prefix, suffix)` pair for a word, insert every suffix of `word + '{' + word`. With maximum word length `W`, this is `O(W)` inserted paths of length `O(W)`, so build time/space are `O(N * W^2)` and query time is `O(prefix length + suffix length)`.
- If the query asks for the largest matching insertion index, process words in increasing index order and overwrite the index at every visited trie node; the stored value is then the largest index matching that node's path.
- A missing query edge means the full key does not match, so return failure (`-1`), not the current node's stored index.
- A trie containing all suffixes/rotations is still a trie; do not call it a suffix tree. A suffix tree is a compressed suffix trie with different construction and invariants.
- Use: autocomplete, word search, longest common prefix, XOR maximum

## 10. Morris Traversal
- O(1) space inorder/preorder using threaded links
- Temporarily modify tree (restore after), no stack needed
- Use: inorder without recursion/stack, space-constrained problems

## 11. Serialize / Deserialize
- Preorder with nulls: encode tree as string, decode by consuming tokens
- Level-order with nulls also works
- Use: codec for binary trees, duplicate subtree detection

## Key Gotchas
- Always clarify: binary tree vs BST vs n-ary tree
- Recursive depth limit for very deep trees (1e5 nodes → use iterative)
- Height-balanced BST operations are O(log n); skewed is O(n)
- Segment Tree Lazy:
    - Forgot to initialize children, null in constructor
    - When a node has no children but the query partially overlaps, return directly only if the parent state uniformly answers the read; for a partial write, push the state into children first
    - read path : only recurse into a child if it exists; 
    - write path : after left/right child update, update the parent from both child states/aggregates





#



