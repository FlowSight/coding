Problem
You are given an integer array values of length n and a binary string state of length n, where state[i] == '1' means index i is currently available.

You must build a sequence s of length m by performing exactly m operations. In each operation:

Choose any index i that is currently available (state[i] == '1') and append values[i] to the end of s.
After the append, update state by flipping to '1' every '0' that is immediately to the right of a '1' (i.e., for each j, if state[j]=='1' and j+1<n and state[j+1]=='0', set state[j+1]='1').
Goal: make the resulting sequence s lexicographically largest among all possible results.

Lexicographic order: compare from left to right; at the first differing element, the larger element wins.

Input
Line 1: integers n and m
Line 2: n integers values
Line 3: binary string state
Output
Print m integers: the constructed sequence s
Example
Input:

4 2
10 5 7 6    
0101
Output:

6 7


import java.util.*;

class Solution {
    public int[] lexicographicallyLargestSequence(int[] values, String state, int m) {
        int n = values.length;
        int[] result = new int[m];

        // Max heap: stores [value, index]
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>(
            (a, b) -> Integer.compare(b[0], a[0])
        );

        boolean[] unlocked = new boolean[n];
        int rightmostUnlocked = -1;

        // Initialize available indices
        for (int i = 0; i < n; i++) {
            if (state.charAt(i) == '1') {
                unlocked[i] = true;
                maxHeap.offer(new int[]{values[i], i});
                rightmostUnlocked = Math.max(rightmostUnlocked, i);
            }
        }

        for (int step = 0; step < m; step++) {

            // Pick lexicographically largest available value
            int[] best = maxHeap.poll();
            result[step] = best[0];

            // Preserve current frontier for simultaneous expansion
            int limit = rightmostUnlocked;

            // Expand one layer to the right
            for (int i = 0; i <= limit; i++) {
                if (i + 1 < n && unlocked[i] && !unlocked[i + 1]) {
                    unlocked[i + 1] = true;
                    maxHeap.offer(new int[]{values[i + 1], i + 1});
                    rightmostUnlocked = Math.max(rightmostUnlocked, i + 1);
                }
            }
        }

        return result;
    }
}