// Min hotels to accommodate group, tie-break on minimum total capacity
// Greedy for min count + DP for min sum with exactly k elements >= target
//
// Time: O(n * k * totalSum) for DP phase
// Space: O(k * totalSum)
// 14 may 2026
// sev0..sev0..sev0

#include <bits/stdc++.h>
using namespace std;

pair<int, int> minHotels(vector<int>& capacities, int groupSize) {
    int n = capacities.size();
    if (n == 0 || groupSize <= 0) return {0, 0};

    // Step 1: Find minimum k (greedy — pick largest first)
    sort(capacities.begin(), capacities.end(), greater<int>());
    int k = 0, runningSum = 0;
    for (int i = 0; i < n; i++) {
        runningSum += capacities[i];
        k++;
        if (runningSum >= groupSize) break;
    }
    if (runningSum < groupSize) return {-1, -1}; // impossible

    // Step 2: Find minimum total capacity using exactly k hotels with sum >= groupSize
    // Sort ascending for DP
    sort(capacities.begin(), capacities.end());
    int totalSum = accumulate(capacities.begin(), capacities.end(), 0);

    // dp[j][s] = true if we can pick exactly j elements summing to s
    // 0/1 knapsack style: iterate elements, update in reverse
    vector<vector<bool>> dp(k + 1, vector<bool>(totalSum + 1, false));
    dp[0][0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = min(i + 1, k); j >= 1; j--) {
            for (int s = totalSum; s >= capacities[i]; s--) {
                if (dp[j - 1][s - capacities[i]]) {
                    dp[j][s] = true;
                }
            }
        }
    }

    // Find minimum sum >= groupSize achievable with exactly k elements
    int minTotal = -1;
    for (int s = groupSize; s <= totalSum; s++) {
        if (dp[k][s]) {
            minTotal = s;
            break;
        }
    }

    return {k, minTotal};
}

int main() {
    // Test 1: [1,2,3,4,5], group=7 → k=2, min_total=7 (pick [3,4] or [2,5])
    vector<int> cap1 = {1, 2, 3, 4, 5};
    auto [k1, t1] = minHotels(cap1, 7);
    cout << "Test 1: hotels=" << k1 << ", total=" << t1 << endl;

    // Test 2: [5,5,5,10], group=12 → k=2, min_total=15 (pick [5,10])
    vector<int> cap2 = {5, 5, 5, 10};
    auto [k2, t2] = minHotels(cap2, 12);
    cout << "Test 2: hotels=" << k2 << ", total=" << t2 << endl;

    // Test 3: [3,3,3,3], group=10 → k=4, min_total=12 (must use all)
    vector<int> cap3 = {3, 3, 3, 3};
    auto [k3, t3] = minHotels(cap3, 10);
    cout << "Test 3: hotels=" << k3 << ", total=" << t3 << endl;

    // Test 4: [1,2,3], group=10 → impossible
    vector<int> cap4 = {1, 2, 3};
    auto [k4, t4] = minHotels(cap4, 10);
    cout << "Test 4: hotels=" << k4 << ", total=" << t4 << endl;

    // Test 5: [10,1,1,1,8], group=9 → k=1, min_total=10 (pick [10])
    vector<int> cap5 = {10, 1, 1, 1, 8};
    auto [k5, t5] = minHotels(cap5, 9);
    cout << "Test 5: hotels=" << k5 << ", total=" << t5 << endl;

    return 0;
}
