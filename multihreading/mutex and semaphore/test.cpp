/*
 * Minimum operations to sort an array in ascending order
 * Ops: 1) Reverse entire array   2) Move first element to end (rotate left by 1)
 * Constraint: guaranteed the permutation is sortable with these ops.
 *
 * Insight: reverse + rotate generate the Dihedral group → only 2n reachable states.
 *   arr (or its reverse) must be a rotation of sorted.
 *   Count descents to find rotation offset, then use closed-form cost.  O(n).
 *
 * LC#: N/A | Severity: Medium | Pattern: Math / Dihedral Group
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Returns rotation offset k if `a` is a rotation of sorted order, else -1.
// A valid rotation has at most 1 circular descent.
int getRotation(const vector<int>& a) {
    int n = a.size(), breaks = 0, pos = -1;
    for (int i = 0; i < n; i++)
        if (a[i] > a[(i + 1) % n]) { breaks++; pos = i; }
    if (breaks == 0) return 0;
    if (breaks != 1) return -1;  // >1 descent → not a rotation of sorted
    return (pos + 1) % n;
}

int minOpsToSort(vector<int> arr) {
    int n = arr.size();
    vector<int> sorted(arr);
    sort(sorted.begin(), sorted.end());
    if (arr == sorted) return 0;

    int ans = n; // upper bound

    // Case 1: arr is a rotation of sorted
    int k = getRotation(arr);
    if (k > 0) ans = min(k, n - k + 2);  // k rotates  OR  rev + (n-k) rotates + rev

    // Case 2: reverse(arr) is a rotation of sorted
    vector<int> rev(arr.rbegin(), arr.rend());
    int j = getRotation(rev);
    if (j >= 0) ans = min(ans, min(j + 1, n - j + 1));  // rev + j rotates  OR  (n-j) rotates + rev

    return ans;
}

int main() {
    vector<pair<vector<int>, string>> tests = {
        {{1, 2, 3},       "Already sorted      "},
        {{3, 2, 1},       "Just reverse        "},
        {{1, 3, 2},       "2 ops               "},
        {{3, 1, 2},       "1 rotation          "},
        {{4, 3, 2, 1},    "Reverse (n=4)       "},
        {{4, 1, 2, 3},    "1 rotation (n=4)    "},
        {{2, 3, 4, 1},    "3 rotations (n=4)   "},
        {{2, 1, 4, 3},    "F_2 (n=4) expect 3  "},
        {{3, 2, 1, 4},    "F_3 (n=4) expect 2  "},
        {{1, 4, 3, 2},    "F_1 (n=4) expect 2  "},
        {{5, 1, 2, 3, 4}, "1 rotation (n=5)    "},
    };

    for (auto& [arr, desc] : tests) {
        cout << desc << ":  [";
        for (int i = 0; i < (int)arr.size(); i++)
            cout << arr[i] << (i + 1 < (int)arr.size() ? "," : "");
        cout << "] -> " << minOpsToSort(arr) << " ops\n";
    }
    return 0;
}
