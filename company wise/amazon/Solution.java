/*
 * Minimum operations to sort an array in ascending order
 * Ops: 1) Reverse entire array   2) Move first element to end (rotate left by 1)
 * Constraint: guaranteed the permutation is sortable with these ops.
 *
 * Insight: reverse + rotate generate the Dihedral group → only 2n reachable states.
 *   arr (or its reverse) must be a rotation of sorted.
 *   Count descents to find rotation offset, then use closed-form cost.  O(n).
 */

import java.util.*;

public class Solution {

    // Returns rotation offset k if `a` is a rotation of sorted order, else -1.
    // A valid rotation has at most 1 circular descent.
    static int getRotation(List<Integer> a) {
        int n = a.size(), breaks = 0, pos = -1;
        for (int i = 0; i < n; i++)
            if (a.get(i) > a.get((i + 1) % n)) { breaks++; pos = i; }
        if (breaks == 0) return 0;
        if (breaks != 1) return -1;  // >1 descent → not a rotation of sorted
        return (pos + 1) % n;
    }

    public static int minOpsToSort(List<Integer> arr) {
        int n = arr.size();
        List<Integer> sorted = new ArrayList<>(arr);
        Collections.sort(sorted);
        if (arr.equals(sorted)) return 0;

        int ans = n;

        // Case 1: arr is a rotation of sorted
        int k = getRotation(arr);
        if (k > 0) ans = Math.min(k, n - k + 2);

        // Case 2: reverse(arr) is a rotation of sorted
        List<Integer> rev = new ArrayList<>(arr);
        Collections.reverse(rev);
        int j = getRotation(rev);
        if (j >= 0) ans = Math.min(ans, Math.min(j + 1, n - j + 1));

        return ans;
    }

    public static void main(String[] args) {
        List<List<Integer>> inputs = List.of(
            List.of(1, 2, 3),
            List.of(3, 2, 1),
            List.of(1, 3, 2),
            List.of(3, 1, 2),
            List.of(4, 3, 2, 1),
            List.of(4, 1, 2, 3),
            List.of(2, 3, 4, 1),
            List.of(2, 1, 4, 3),
            List.of(3, 2, 1, 4),
            List.of(1, 4, 3, 2),
            List.of(5, 1, 2, 3, 4)
        );
        String[] descs = {
            "Already sorted      ",
            "Just reverse        ",
            "2 ops               ",
            "1 rotation          ",
            "Reverse (n=4)       ",
            "1 rotation (n=4)    ",
            "3 rotations (n=4)   ",
            "F_2 (n=4) expect 3  ",
            "F_3 (n=4) expect 2  ",
            "F_1 (n=4) expect 2  ",
            "1 rotation (n=5)    ",
        };

        for (int t = 0; t < inputs.size(); t++) {
            int res = minOpsToSort(inputs.get(t));
            System.out.println(descs[t] + ":  " + inputs.get(t)
                + " -> " + res + " ops");
        }
    }
}


5 4 3 2 1
4 3 2 1 5
5 1 2 3 4
1 2 3 4 5