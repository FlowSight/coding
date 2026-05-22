/*
 * Problem: Max Sum of B where B[i] > A[i]
 * Difficulty: Medium
 * Pattern: Greedy / Multiset
 *
 * Given two integer arrays a and b of size n:
 * - You can sort b (but not a)
 * - Maximize the sum of all b[i] where b[i] > a[i]
 *
 * Approach:
 *   Sort b descending. For each b value, greedily pair it with the
 *   LARGEST a[i] it can strictly beat. This preserves smaller a values
 *   for future (smaller) b values to also win.
 *
 *   Use a multiset for O(log n) lookup of largest a < b_val.
 *
 * Time: O(n log n), Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

long long maxSum(vector<int>& a, vector<int>& b) {
    sort(b.rbegin(), b.rend());
    multiset<int> ms(a.begin(), a.end());

    long long sum = 0;
    for (int bval : b) {
        auto it = ms.lower_bound(bval); // first a >= bval
        if (it != ms.begin()) {
            --it;                        // largest a < bval
            sum += bval;
            ms.erase(it);
        } else {
            //ms.erase(ms.begin());        // can't win, discard smallest
        }
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;

    cout << maxSum(a, b) << "\n";
    return 0;
}
