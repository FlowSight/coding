/*
 * LC#: N/A (Job Sequencing Problem)
 * Difficulty: Medium-Hard
 * Pattern: Union-Find / Disjoint Set Union
 *
 * Optimal Task Scheduling to Maximize Rewards Before Deadlines
 *
 * Approach: Sort tasks by reward descending, then use Union-Find to
 * efficiently find the latest available time slot <= deadline for each task.
 *
 * Time: O(n log n) for sorting + O(n * α(n)) for scheduling ≈ O(n log n)
 * Space: O(max_deadline)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Task {
    string id;
    int deadline;
    int reward;
};

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) : parent(n + 1) {
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    // Find the latest available slot <= x
    int find(int x) {
        if (x < 0) return -1;
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    // Mark slot x as used by pointing it to slot x-1
    void unite(int x) {
        int px = find(x);
        if (px > 0)
            parent[px] = px - 1;
    }
};

vector<string> scheduleTasksMaxReward(vector<Task>& tasks) {
    // Sort by reward descending
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.reward > b.reward;
    });

    // Find maximum deadline
    int maxDeadline = 0;
    for (auto& t : tasks)
        maxDeadline = max(maxDeadline, t.deadline);

    UnionFind uf(maxDeadline);

    // result[slot] = task_id scheduled at that slot
    vector<string> slots(maxDeadline + 1, "");
    int totalReward = 0;

    for (auto& task : tasks) {
        // Find the latest available slot <= task.deadline
        int availableSlot = uf.find(task.deadline);
        if (availableSlot > 0) {
            slots[availableSlot] = task.id;
            totalReward += task.reward;
            uf.unite(availableSlot); // mark slot as used
        }
    }

    // Collect scheduled tasks in order of time slots
    vector<string> result;
    for (int i = 1; i <= maxDeadline; i++) {
        if (!slots[i].empty())
            result.push_back(slots[i]);
    }

    cout << "Total reward: " << totalReward << endl;
    return result;
}

int main() {
    vector<Task> tasks = {
        {"a", 2, 8},
        {"b", 1, 3},
        {"c", 2, 5},
        {"d", 3, 3}
    };

    cout << "Input: [(a,2,8), (b,1,3), (c,2,5), (d,3,3)]" << endl;
    vector<string> result = scheduleTasksMaxReward(tasks);

    cout << "Optimal order: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Additional test case
    cout << "\n--- Test 2 ---" << endl;
    vector<Task> tasks2 = {
        {"t1", 1, 10},
        {"t2", 1, 20},
        {"t3", 2, 15},
        {"t4", 2, 5},
        {"t5", 3, 1}
    };
    vector<string> result2 = scheduleTasksMaxReward(tasks2);
    cout << "Optimal order: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
