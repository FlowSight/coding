// Date: 25Aug26
// Pattern: geometry / convex hull (Andrew's Monotone Chain)
// True convex-hull LeetCode reference: LC 587 - Erect the Fence
//   (the fence enclosing all trees IS the convex hull boundary)
// Notes: sort by (x,y), build lower hull then upper hull using cross-product turns.
//        O(n log n) total (sort dominates); hull construction itself is O(n).

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

// cross product of (O->A) x (O->B). >0 = counter-clockwise turn, <0 = clockwise, 0 = collinear
ll cross(const pll &O, const pll &A, const pll &B) {
    return (A.first - O.first) * (B.second - O.second) -
           (A.second - O.second) * (B.first - O.first);
}

// Returns hull points in counter-clockwise order, starting from the lowest point.
// Collinear boundary points are EXCLUDED (strict hull) — flip cross<=0 to cross<0 to include them.
vector<pll> convexHull(vector<pll> pts) {
    int n = pts.size(), k = 0;
    if (n < 3) return pts;

    sort(pts.begin(), pts.end());
    vector<pll> hull(2 * n);

    // build lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }

    // build upper hull
    for (int i = n - 2, lower = k + 1; i >= 0; i--) {
        while (k >= lower && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }

    hull.resize(k - 1); // last point == first point, drop the duplicate
    return hull;
}

// ---- Brute-force ground truth (STRICT hull, matches convexHull()'s collinear-exclusion convention):
// point i is a hull vertex iff there's SOME direction where i is the unique extreme point
// (i.e. i is not "hidden" behind another point, and not collinear-redundant on an edge).
vector<pll> bruteForceHull(vector<pll> pts) {
    int n = pts.size();
    vector<pll> result;
    for (int i = 0; i < n; i++) {
        bool isVertex = false;
        for (int dir = 0; dir < 360 && !isVertex; dir++) {
            double rad = dir * M_PI / 180.0, dx = cos(rad), dy = sin(rad);
            double best = pts[i].first * dx + pts[i].second * dy;
            bool unique = true;
            for (int k = 0; k < n; k++) {
                if (k == i) continue;
                double v = pts[k].first * dx + pts[k].second * dy;
                if (v > best - 1e-9) { unique = false; break; } // beaten or tied -> not unique extreme here
            }
            if (unique) isVertex = true;
        }
        if (isVertex) result.push_back(pts[i]);
    }
    return result;
}

int main() {
    // Quick manual sanity check
    vector<pll> pts = {{0,0},{1,1},{2,2},{2,0},{0,2},{1,0},{0,1}}; // square + collinear points
    auto hull = convexHull(pts);
    cout << "Hull (CCW): ";
    for (auto [x,y] : hull) cout << "(" << x << "," << y << ") ";
    cout << "\n";

    // Randomized stress test vs brute force
    mt19937 rng(42);
    int mismatches = 0, trials = 2000;
    for (int t = 0; t < trials; t++) {
        int n = uniform_int_distribution<int>(3, 12)(rng);
        set<pll> ptset;
        while ((int)ptset.size() < n)
            ptset.insert({uniform_int_distribution<int>(0,10)(rng), uniform_int_distribution<int>(0,10)(rng)});
        vector<pll> p(ptset.begin(), ptset.end());

        auto fast = convexHull(p);
        auto brute = bruteForceHull(p);
        set<pll> fastSet(fast.begin(), fast.end()), bruteSet(brute.begin(), brute.end());

        if (fastSet != bruteSet) {
            mismatches++;
            cout << "MISMATCH on trial " << t << " with " << n << " points\n";
        }
    }
    cout << "Stress test: " << trials << " trials, " << mismatches << " mismatches\n";
    return 0;
}
