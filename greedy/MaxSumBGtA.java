/*
 * Problem: Max Sum of B where B[i] > A[i]
 * Pattern: Greedy / TreeMap
 *
 * Sort b descending. For each b value, pair with largest a it can strictly beat.
 * Time: O(n log n), Space: O(n)
 */

import java.util.*;

public class MaxSumBGtA {
    public static long maxSum(List<Integer> a, List<Integer> b) {
        List<Integer> sortedB = new ArrayList<>(b);
        sortedB.sort(Collections.reverseOrder());

        TreeMap<Integer, Integer> map = new TreeMap<>();
        for (int x : a) map.merge(x, 1, Integer::sum);

        long sum = 0;
        for (int bval : sortedB) {
            Integer key = map.lowerKey(bval); // largest a strictly < bval
            if (key != null) {
                sum += bval;
                if (map.get(key) == 1) map.remove(key);
                else map.merge(key, -1, Integer::sum);
            } else {
                int first = map.firstKey();
                if (map.get(first) == 1) map.remove(first);
                else map.merge(first, -1, Integer::sum);
            }
        }
        return sum;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Integer> a = new ArrayList<>(), b = new ArrayList<>();
        for (int i = 0; i < n; i++) a.add(sc.nextInt());
        for (int i = 0; i < n; i++) b.add(sc.nextInt());
        System.out.println(maxSum(a, b));
    }
}
