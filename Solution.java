import java.util.*;

public class Solution {

    public static List<Integer> getFirstCompatible(List<Integer> arr1, List<Integer> arr2) {
        int n = arr1.size(), m = arr2.size();

        // pair: [value, original index]
        int[][] sortedArr2 = new int[m][2];
        for (int i = 0; i < m; i++) {
            sortedArr2[i][0] = arr2.get(i);
            sortedArr2[i][1] = i;
        }
        Arrays.sort(sortedArr2, (a, b) -> Integer.compare(a[0], b[0]));

        // suffix minimum of original indices
        int[] suffMin = new int[m];
        suffMin[m - 1] = sortedArr2[m - 1][1];
        for (int i = m - 2; i >= 0; i--) {
            suffMin[i] = Math.min(sortedArr2[i][1], suffMin[i + 1]);
        }

        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int target = arr1.get(i);
            // binary search for first value > target
            int lo = 0, hi = m;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (sortedArr2[mid][0] > target) hi = mid;
                else lo = mid + 1;
            }
            if (lo == m) ans.add(-1);
            else ans.add(suffMin[lo] + 1); // 1-based
        }
        return ans;
    }

    public static void main(String[] args) {
        // TC1
        System.out.println("TC1: " + getFirstCompatible(
            Arrays.asList(3, 8, 1), Arrays.asList(1, 2, 5)));

        // TC2
        System.out.println("TC2: " + getFirstCompatible(
            Arrays.asList(5, 1, 7, 4), Arrays.asList(1, 2, 3, 5)));

        // TC3
        System.out.println("TC3: " + getFirstCompatible(
            Arrays.asList(2, 8, 7, 4, 6), Arrays.asList(3, 5, 7, 3)));
    }
}
