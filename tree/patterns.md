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

## 7. Segment Tree on Tree (HLD)
- Heavy-Light Decomposition: decompose into chains for path queries
- Each chain handled by segment tree — O(log^2 n) per query
- Use: path sum/max queries, subtree queries with updates
- array value ranges are huge : just take array, do ops on index (coordinate compression)
- dont put actual hydrated array, use logical array, use left,right,mid

## 8. Trie (Prefix Tree)
- Each edge = character, node = prefix endpoint
- Use: autocomplete, word search, longest common prefix, XOR maximum

## 9. Morris Traversal
- O(1) space inorder/preorder using threaded links
- Temporarily modify tree (restore after), no stack needed
- Use: inorder without recursion/stack, space-constrained problems

## 10. Serialize / Deserialize
- Preorder with nulls: encode tree as string, decode by consuming tokens
- Level-order with nulls also works
- Use: codec for binary trees, duplicate subtree detection

## Key Gotchas
- Always clarify: binary tree vs BST vs n-ary tree
- Recursive depth limit for very deep trees (1e5 nodes → use iterative)
- Height-balanced BST operations are O(log n); skewed is O(n)
