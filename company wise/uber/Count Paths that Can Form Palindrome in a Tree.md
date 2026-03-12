Given a tree with $n$ nodes (numbered $0, 1, ..., n-1$), each having a character on it. You need to find the number of paths from a given node to the root that can form a palindrome. \n \n Input Parameters:\n - Integer $treeNodes$: Number of nodes in the tree\n - Character array $nodes$: Characters on the nodes, nodes[0] is the root\n - Integer array $nodeFrom$: Start node of edges\n - Integer array $nodeTo$: End node of edges, nodeFrom[i] has an edge to nodeTo[i]\n - Integer array $queries$: Query start nodes\n \n Output:\n Return an integer array with the count of palindrome-forming paths for each query. \n \n Example:\n \n $treeNodes = 4$, $nodes = ['z', 'a', 'a', 'a']$, $nodeFrom = [0, 0, 1]$, $nodeTo = [1, 2, 3]$, $queries = [3]$\n \n For query node $3$, the path to root is $3(a) \to 1(a) \to 0(z)$,\n - Ending at node $3$, form palindrome "a"\n - Ending at node $1$, form palindrome "aa"\n - Ending at node $0$, form palindrome "aza"\n \n So expected result is $[3]$.

Example
Input
4\nz a a a\n0 0 1\n1 2 3\n3
Output
[3]
