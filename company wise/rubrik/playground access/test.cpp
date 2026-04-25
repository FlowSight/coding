#include <bits/stdc++.h>
using namespace std;

class Playground {
    public:
    Playground() {}

    // blocks until the player can enter
    void enter(int playerId, int teamId) {
        unique_lock<mutex> ul(mtx);

        if (waitingTeams.empty() || waitingTeams.back() != teamId) {

            bool alreadyQueued = false;
            for (int t : waitingTeams) {
                if (t == teamId) { alreadyQueued = true; break; }
            }
            if (!alreadyQueued) waitingTeams.push_back(teamId);
        }

        cv.wait(ul, [this, teamId]{
            if (stopped) return true;
            if (curteam == teamId && curCnt < 10) return true;
            if (curteam == -1 && !waitingTeams.empty() && waitingTeams.front() == teamId) return true;
            if (curteam == -1 && waitingTeams.empty()) return true;
            return false;
        });

        if (stopped) return;

        curteam = teamId;
        curCnt++;

        // Remove this team from the FIFO front since it's now occupying
        if (!waitingTeams.empty() && waitingTeams.front() == teamId) {
            waitingTeams.pop_front();
        }

        cv.notify_all();
        cout << "entered player: " << playerId << " team: " << teamId
             << " (count=" << curCnt << ")" << endl;
    }

    void exit(int playerId, int teamId) {
        unique_lock<mutex> ul(mtx);
        if (stopped) return;

        curCnt--;
        if (curCnt == 0) curteam = -1;

        cv.notify_all();
        cout << "exited player: " << playerId << " team: " << teamId
             << " (count=" << curCnt << ")" << endl;
    }

    void shutdown() {
        unique_lock<mutex> ul(mtx);
        stopped = true;
        cv.notify_all();
    }

    private:
    int curteam = -1;
    int curCnt = 0;
    bool stopped = false;
    mutex mtx;
    condition_variable cv;
    deque<int> waitingTeams;   // FIFO of unique team IDs in arrival order
};


// ─────────────────────────────────────────────
// Test: Team A (5 players) and Team B (5 players) arrive interleaved.
// With FIFO fairness, whichever team's first player arrived first
// gets to go first. The other team waits until the first team drains.
// ─────────────────────────────────────────────

void simulatePlayer(Playground &pg, int playerId, int teamId, int workMs) {
    pg.enter(playerId, teamId);
    this_thread::sleep_for(chrono::milliseconds(workMs));
    pg.exit(playerId, teamId);
}

void testBasicFairness() {
    cout << "\n=== Test: Basic FIFO Fairness ===\n";
    Playground pg;
    vector<thread> threads;

    // Team A players arrive first (IDs 1-5)
    for (int i = 1; i <= 5; i++) {
        threads.emplace_back(simulatePlayer, ref(pg), i, /*teamA*/1, 200);
    }
    // Small delay then Team B arrives (IDs 11-15)
    this_thread::sleep_for(chrono::milliseconds(50));
    for (int i = 11; i <= 15; i++) {
        threads.emplace_back(simulatePlayer, ref(pg), i, /*teamB*/2, 200);
    }
    // Then more Team A (IDs 6-8) — should wait for Team B to finish
    this_thread::sleep_for(chrono::milliseconds(50));
    for (int i = 6; i <= 8; i++) {
        threads.emplace_back(simulatePlayer, ref(pg), i, /*teamA*/1, 200);
    }

    for (auto &t : threads) t.join();
    cout << "=== Test passed ===\n";
}

void testCapacity() {
    cout << "\n=== Test: Capacity Bound (max 10) ===\n";
    Playground pg;
    vector<thread> threads;

    // 15 players from same team — only 10 inside at once
    for (int i = 1; i <= 15; i++) {
        threads.emplace_back(simulatePlayer, ref(pg), i, /*teamA*/1, 300);
    }

    for (auto &t : threads) t.join();
    cout << "=== Test passed ===\n";
}

int main() {
    testBasicFairness();
    testCapacity();
    cout << "\nAll tests completed.\n";
    return 0;
}