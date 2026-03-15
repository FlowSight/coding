// I have an algorithm problem to share. Consider a tree node: 
// `Node(score *left *right numNodesInLeftSubtree numNodesInRightSubtree)`. 
// For example, a tree might look like this: 
// `5 (1, 3) / \ 4 7 (1, 1) / \ 6 8`. 
// Each node's `val` is its score, and each node contains the number
//  of nodes in its left and right subtrees. The task is to implement
//   two methods: one to calculate the rank based on the score, and another
//    to calculate the corresponding score based on the rank. For example,
//     given a score of 6, it should return 3; given a rank of 1, it should return 8.
