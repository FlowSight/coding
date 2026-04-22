Given a positive integer array w of length n, design a data structure that supports:

Initialization with w.
pickIndex(): randomly return an index i (0 <= i < n) such that the probability of returning i is w[i] / sum(w).
Requirements:

pickIndex() should be efficient and suitable for being called many times.
Explain how you generate randomness and ensure the distribution is correct.
Constraints

1 <= n <= 2 * 10^5
1 <= w[i] <= 10^5
Number of calls to pickIndex() can be up to 2 * 10^5
Test cases

Input: w = [1]. Calling pickIndex() multiple times should always return 0.
Input: w = [1, 3]. Over many calls, index 0 should appear about 0.25 and index 1 about 0.75.
Input: w = [2, 5, 3]. Frequencies should roughly follow ratio 2:5:3.
Edge: very large n and large total weight should still work within acceptable time.
Randomness: different runs may yield different sequences, but the empirical distribution should be stable.
Example
Input
1
1
5
pick
pick
pick
pick
pick
Output
0
0
0
0
0