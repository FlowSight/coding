#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Rerooting DP - O(n) time, O(n) space
// Cities are 1-indexed in input, result[i] = answer for city (i+1)
vector<int> countReverseEdges(int n, int edges, vector<int>& gfrom, vector<int>& gto) {
    // Convert to 0-indexed; weight 0 = original direction (free), 1 = reversed (costs 1)
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < edges; i++) {
        int u = gfrom[i] - 1, v = gto[i] - 1;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 1});
    }

    vector<int> ans(n, 0);
    vector<bool> visited(n, false);

    // BFS1: compute ans[0] = cost for node 0 to reach all others
    vector<int> stk;
    stk.push_back(0);
    visited[0] = true;
    int cost0 = 0;

    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (auto& [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                cost0 += w;
                stk.push_back(v);
            }
        }
    }
    ans[0] = cost0;

    // BFS2: reroot - ans[child] = ans[parent] + 1 - 2*w
    fill(visited.begin(), visited.end(), false);
    visited[0] = true;
    stk.push_back(0);

    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (auto& [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                ans[v] = ans[u] + 1 - 2 * w;
                stk.push_back(v);
            }
        }
    }

    return ans;
}

// ---------- Test Harness ----------
void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i] << (i + 1 < (int)v.size() ? ", " : "");
    }
    cout << "]" << endl;
}

int main() {
    // Test 1: n=4, edges: 1->4, 2->4, 3->4 (star toward 4)
    {
        int n = 4, edges = 3;
        vector<int> gfrom = {1, 2, 3}, gto = {4, 4, 4};
        cout << "Test 1: ";
        printVec(countReverseEdges(n, edges, gfrom, gto));
        // Expected: [2, 2, 2, 3]
    }

    // Test 2: n=4, edges: 1->2, 2->3, 3->4 (chain)
    {
        int n = 4, edges = 3;
        vector<int> gfrom = {1, 2, 3}, gto = {2, 3, 4};
        cout << "Test 2: ";
        printVec(countReverseEdges(n, edges, gfrom, gto));
        // Expected: [0, 1, 2, 3]
    }

    return 0;
}