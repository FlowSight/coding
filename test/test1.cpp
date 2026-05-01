/*
 * Drone Delivery on a Circular Hub Network
 *
 * n hubs arranged in a circle, numbered 1..n (1-indexed).
 * transitionTime[i-1] = cost to LEAVE hub i (same cost either direction).
 * deliverySequence = ordered list of hubs (1-indexed) to deliver to.
 * Drone starts at hub 1.
 *
 * Per-node cost model:
 *   CW from a to b  = sum of T for each hub departed (a, a+1, ..., b-1)
 *   CCW from a to b = totalSum - T[b] + T[a] - CW
 *
 * Time: O(n + m)   Space: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

long long minTravelTime(vector<int>& transitionTime, vector<int>& deliverySequence) {
    int n = transitionTime.size();

    // prefix[i] = sum of transitionTime[0..i-1]  (0-indexed internally)
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + transitionTime[i];
    long long totalSum = prefix[n];

    // CW cost from hub a to hub b (0-indexed)
    auto cwCost = [&](int a, int b) -> long long {
        if (a <= b) return prefix[b] - prefix[a];
        return totalSum - prefix[a] + prefix[b]; // wrap around
    };

    // min distance using per-node departure cost
    auto minDist = [&](int a, int b) -> long long {
        if (a == b) return 0;
        long long cw  = cwCost(a, b);
        long long ccw = totalSum - transitionTime[b] + transitionTime[a] - cw;
        return min(cw, ccw);
    };

    long long total = 0;
    int curr = 0; // drone starts at hub 1 (1-indexed) = hub 0 (0-indexed)
    for (int hub : deliverySequence) {
        int h = hub - 1; // convert 1-indexed to 0-indexed
        total += minDist(curr, h);
        curr = h;
    }
    return total;
}

int main() {
    // --- Test 1: failing test case ---
    // 2 hubs, T = {1, 2}, delivery = {1, 2, 1}
    // Start at hub 1.  1→2: min(1,1)=1.  2→1: min(2,2)=2.  Total = 3
    {
        vector<int> time = {1, 2};
        vector<int> del  = {1, 2, 1};
        cout << "Test 1: " << minTravelTime(time, del) << endl; // Expected: 3
    }

    // --- Test 2: 6 hubs ---
    // T = {3,2,5,1,4,6}, delivery = {1,5,4}
    // Start at hub 1.
    // 1→5: CW(0,4)=11, CCW=21-4+3-11=9 → 9
    // 5→4: CW(4,3)=20, CCW=21-1+4-20=4 → 4
    // Total = 13
    {
        vector<int> time = {3, 2, 5, 1, 4, 6};
        vector<int> del  = {1, 5, 4};
        cout << "Test 2: " << minTravelTime(time, del) << endl; // Expected: 13
    }

    // --- Test 3: deliver to start hub ---
    {
        vector<int> time = {3, 2, 5, 1, 4, 6};
        vector<int> del  = {1};
        cout << "Test 3 (same hub): " << minTravelTime(time, del) << endl; // Expected: 0
    }

    // --- Test 4: single delivery across ring ---
    // 1→4 (0-indexed: 0→3)
    // CW = T[0]+T[1]+T[2] = 10
    // CCW = 21 - T[3] + T[0] - 10 = 21-1+3-10 = 13
    // min = 10
    {
        vector<int> time = {3, 2, 5, 1, 4, 6};
        vector<int> del  = {4};
        cout << "Test 4 (to hub 4): " << minTravelTime(time, del) << endl; // Expected: 10
    }

    // --- Test 5: hubs={2,3,3,1}, time={3,2,1} ---
    // 1→2:3  2→3:2  3→3:0  3→1:1  Total=6
    {
        vector<int> time = {3, 2, 1};
        vector<int> del  = {2, 3, 3, 1};
        cout << "Test 5: " << minTravelTime(time, del) << endl; // Expected: 6
    }

    return 0;
}
