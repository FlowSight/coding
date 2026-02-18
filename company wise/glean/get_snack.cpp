// You are given a matrix where each cell can have values

// D - your desk
// B - Boss's desk (can be multiple)
// S - Snack (can be multiple)
// . - empty
// # - wall

// first question -> Find if it's possible to get a snack from your desk without disturbing any boss.
// BFS

// second question ->
// If the snack has a noise value K. K represnt the number of empty spaces the noise can travel through. find if its' possible to get the snack without disturbing any boss' through noise.

// sol. first do multisource bfs from All B's and store min distance of a cell from any B's. then do a BFS from D to S such that you do not use any points where dist(cell) <= k from B

// third question ->

// Find the maximum value of K for which you can get the snack without distrubing any B's.

// Binary Search on K with the solution of 2nd.