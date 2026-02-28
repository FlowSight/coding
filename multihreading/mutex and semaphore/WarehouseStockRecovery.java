/*
 * Warehouse Stock Recovery
 * -------------------------
 * Given: array warehouseStockLevels where -1 = missing data.
 * Rule : every warehouse must have at least one neighbour with stock >= its own.
 *        arr[0] <= arr[1],  arr[n-1] <= arr[n-2],
 *        interior i: arr[i] <= arr[i-1] OR arr[i] <= arr[i+1]
 *        (equivalently: no element is a strict local maximum)
 *
 * Replace every -1 with a value in [1, 200].
 * Return the number of valid replacements modulo 998244353.
 *
 * Approach – DP with prefix/suffix sums  O(200 · n)
 * --------------------------------------------------
 * dp[v][0] = #ways where position i has value v AND its constraint is already satisfied
 * dp[v][1] = #ways where position i has value v AND it still NEEDS arr[i+1] >= v
 *
 * Position 0 always needs arr[1] >= arr[0]  →  base sets dp[v][1] = 1.
 *
 * Interior transition (position i → i+1, where i+1 < n-1):
 *   new[w][0] = suffixSum0[w]  +  dp[w][1]         (left neighbour >= w  satisfies i+1;
 *                                                     dp[w][1] covers must-case w = v)
 *   new[w][1] = prefixTotal[w-1]                    (left < w → needs right help)
 *
 * Last position (i+1 = n-1): must also satisfy arr[n-1] <= arr[n-2] (w <= v):
 *   new[w][0] = suffixSum0[w]  +  dp[w][1]          (same formula)
 *   new[w][1] = 0                                    (no right neighbour to help)
 *
 * Answer: Σ dp[v][0] over all v at position n-1.
 */

import java.util.*;

public class WarehouseStockRecovery {

    static final int MOD = 998244353;
    static final int MAX_VAL = 200;

    public static int countRecoveryWays(List<Integer> arr) {
        int n = arr.size();
        if (n == 0) return 0;
        if (n == 1) return arr.get(0) == -1 ? MAX_VAL : 1;

        // dp[v][must]  v in 1..MAX_VAL
        long[][] dp = new long[MAX_VAL + 1][2];

        // --- base: position 0, must = 1 (needs arr[1] >= arr[0]) ---
        if (arr.get(0) == -1) {
            for (int v = 1; v <= MAX_VAL; v++) dp[v][1] = 1;
        } else {
            dp[arr.get(0)][1] = 1;
        }

        // --- process positions 1 .. n-1 ---
        for (int i = 1; i < n; i++) {
            boolean isLast = (i == n - 1);

            // suffix sum of dp[*][0]:  sufS0[w] = Σ_{v=w}^{MAX_VAL} dp[v][0]
            long[] sufS0 = new long[MAX_VAL + 2];
            for (int v = MAX_VAL; v >= 1; v--)
                sufS0[v] = (sufS0[v + 1] + dp[v][0]) % MOD;

            // prefix total: prefT[w] = Σ_{v=1}^{w} (dp[v][0] + dp[v][1])
            long[] prefT = new long[MAX_VAL + 1];
            for (int v = 1; v <= MAX_VAL; v++)
                prefT[v] = (prefT[v - 1] + dp[v][0] + dp[v][1]) % MOD;

            long[][] ndp = new long[MAX_VAL + 1][2];

            int lo = 1, hi = MAX_VAL;
            if (arr.get(i) != -1) { lo = arr.get(i); hi = arr.get(i); }

            for (int w = lo; w <= hi; w++) {
                ndp[w][0] = (sufS0[w] + dp[w][1]) % MOD;
                if (!isLast) {
                    ndp[w][1] = (w >= 2) ? prefT[w - 1] : 0;
                }
            }

            dp = ndp;
        }

        // answer: Σ dp[v][0]
        long ans = 0;
        for (int v = 1; v <= MAX_VAL; v++)
            ans = (ans + dp[v][0]) % MOD;
        return (int) ans;
    }

    // ---- driver ----
    public static void main(String[] args) {

        // Test 1: all unknown, n=1  →  200
        System.out.println("Test 1 (n=1, all -1):  " + countRecoveryWays(List.of(-1)));

        // Test 2: all unknown, n=2  →  200  (must be equal pairs)
        System.out.println("Test 2 (n=2, all -1):  " + countRecoveryWays(List.of(-1, -1)));

        // Test 3: all unknown, n=3
        System.out.println("Test 3 (n=3, all -1):  " + countRecoveryWays(List.of(-1, -1, -1)));

        // Test 4: fixed equal pair → 1
        System.out.println("Test 4 ([3,3]):        " + countRecoveryWays(List.of(3, 3)));

        // Test 5: infeasible [5,3] → 0
        System.out.println("Test 5 ([5,3]):        " + countRecoveryWays(List.of(5, 3)));

        // Test 6: [3,5] → 0 (arr[1]=5 > arr[0]=3 and no right neighbour)
        System.out.println("Test 6 ([3,5]):        " + countRecoveryWays(List.of(3, 5)));

        // Test 7: [-1,5,-1]
        // arr[1]=5 not strict local max ⇒ arr[0]=5 OR arr[2]=5
        // |A|=5, |B|=5, |A∩B|=1 → 9
        System.out.println("Test 7 ([-1,5,-1]):    " + countRecoveryWays(List.of(-1, 5, -1)));

        // Test 8: larger example
        System.out.println("Test 8 ([-1,-1,-1,-1,-1]): "
                + countRecoveryWays(List.of(-1, -1, -1, -1, -1)));

        // Test 9: mixed
        System.out.println("Test 9 ([2,-1,4,-1,3]): "
                + countRecoveryWays(List.of(2, -1, 4, -1, 3)));
    }
}
