/*
 * Playground Access — Team-Exclusive, Bounded Concurrency (max 10)
 *
 * Rules:
 *  1. Only one team can occupy the playground at a time
 *  2. At most 10 players inside concurrently
 *  3. Players from many teams arrive in parallel
 *  4. No starvation: round-robin turn allocation across teams
 *
 * Approach: Round-robin turns with per-turn quota (like CPU time-slice)
 *  - Teams wait in a circular deque
 *  - Current team admits up to `maxPerTurn` players (capacity-bounded)
 *  - After quota hit or team queue empty → DRAIN → rotate to next team
 *  - State machine: IDLE → ADMITTING → DRAINING → IDLE → ...
 *  - Prevents starvation: every team gets a fair turn regardless of queue depth
 *
 * Company: Rubrik SSE
 */

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <cassert>
#include <chrono>
#include <functional>

using namespace std;

class Playground {
public:
    using PlayerTask = function<void()>;

    // cap = max concurrent players, perTurn = max players per team before forced rotation
    explicit Playground(int cap = 10, int perTurn = 5, int numWorkers = 4)
        : capacity(cap), maxPerTurn(perTurn) {
        for (int i = 0; i < numWorkers; i++)
            workers.emplace_back(&Playground::workerLoop, this);
    }

    ~Playground() { shutdown(); }

    void addPlayer(int teamId, PlayerTask task) {
        unique_lock<mutex> lock(mtx);
        teamQueues[teamId].push(move(task));
        submitted++;
        if (!inTurnOrder.count(teamId)) {
            turnOrder.push_back(teamId);
            inTurnOrder.insert(teamId);
        }
        updateState();
        cv.notify_all();
    }

    void waitAll() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() { return completed == submitted; });
    }

    void shutdown() {
        waitAll();
        {
            unique_lock<mutex> lock(mtx);
            if (stopped) return;
            stopped = true;
            cv.notify_all();
        }
        for (auto &w : workers)
            if (w.joinable()) w.join();
        workers.clear();
    }

    int getInside() { lock_guard<mutex> lk(mtx); return inside; }
    int getCurrentTeam() { lock_guard<mutex> lk(mtx); return currentTeam; }

private:
    enum TurnState { IDLE, ADMITTING, DRAINING };

    int capacity;
    int maxPerTurn;
    int inside = 0;
    int currentTeam = -1;
    int servedThisTurn = 0;
    long long submitted = 0;
    long long completed = 0;
    bool stopped = false;
    TurnState state = IDLE;

    deque<int> turnOrder;                              // round-robin queue of team ids
    unordered_set<int> inTurnOrder;                    // O(1) lookup
    unordered_map<int, queue<PlayerTask>> teamQueues;  // per-team task queues
    mutex mtx;
    condition_variable cv;
    vector<thread> workers;

    // Rotate current team out, move to back of deque if it still has players
    void rotateTeam() {
        if (currentTeam == -1) return;
        auto it = teamQueues.find(currentTeam);
        if (it != teamQueues.end() && !it->second.empty()) {
            turnOrder.push_back(currentTeam);   // still has work, re-enqueue
        } else {
            inTurnOrder.erase(currentTeam);
            if (it != teamQueues.end()) teamQueues.erase(it);
        }
        currentTeam = -1;
        servedThisTurn = 0;
    }

    // Drive the state machine forward (idempotent, call whenever state may have changed)
    void updateState() {
        bool changed = true;
        while (changed) {
            changed = false;

            // DRAINING → IDLE: all players from this turn have exited
            if (state == DRAINING && inside == 0) {
                rotateTeam();
                state = IDLE;
                changed = true;
            }

            // ADMITTING → DRAINING: quota reached or team queue empty
            if (state == ADMITTING) {
                auto it = teamQueues.find(currentTeam);
                bool qEmpty = (it == teamQueues.end() || it->second.empty());
                if (servedThisTurn >= maxPerTurn || qEmpty) {
                    state = DRAINING;
                    changed = true;
                }
            }

            // IDLE → ADMITTING: pick next team from round-robin
            if (state == IDLE && !turnOrder.empty()) {
                currentTeam = turnOrder.front();
                turnOrder.pop_front();
                servedThisTurn = 0;
                state = ADMITTING;
                changed = true;
            }
        }
    }

    bool hasQueuedWork() {
        for (auto &[tid, q] : teamQueues)
            if (!q.empty()) return true;
        return false;
    }

    void workerLoop() {
        while (true) {
            PlayerTask task;

            {
                unique_lock<mutex> lock(mtx);

                cv.wait(lock, [&]() {
                    updateState();
                    if (stopped && !hasQueuedWork() && inside == 0) return true;
                    return state == ADMITTING && inside < capacity;
                });

                if (stopped && !hasQueuedWork() && inside == 0) return;

                task = move(teamQueues[currentTeam].front());
                teamQueues[currentTeam].pop();
                servedThisTurn++;
                inside++;

                updateState();  // may transition ADMITTING → DRAINING
            }

            task();

            {
                unique_lock<mutex> lock(mtx);
                inside--;
                completed++;
                updateState();
                cv.notify_all();
            }
        }
    }
};

// ==================== helpers ====================

int playTime(const string &name) {
    int sum = 0;
    for (char c : name) sum += c;
    return 100 + (sum % 200);   // 100-299 ms
}

// ==================== tests ====================

void testSameTeamBasic() {
    cout << "Test 1: 10 players, same team, all enter ... ";
    Playground pg(10, 10, 10);  // cap=10, perTurn=10, workers=10
    for (int i = 0; i < 10; i++)
        pg.addPlayer(0, []() {
            this_thread::sleep_for(chrono::milliseconds(50));
        });
    pg.waitAll();
    assert(pg.getInside() == 0);
    assert(pg.getCurrentTeam() == -1);
    cout << "PASSED\n";
}

void testNoMixing() {
    cout << "Test 2: Two teams, no mixed occupancy ... ";
    const int NUM_TEAMS = 2;
    Playground pg(10, 5, 10);  // cap=10, perTurn=5, workers=10
    atomic<int> teamInside[NUM_TEAMS];
    for (auto &a : teamInside) a = 0;
    atomic<bool> violated{false};

    auto makeTask = [&](int team, const string &name) {
        return [&, team, name]() {
            teamInside[team]++;
            for (int t = 0; t < NUM_TEAMS; t++)
                if (t != team && teamInside[t] > 0) violated = true;
            this_thread::sleep_for(chrono::milliseconds(playTime(name)));
            teamInside[team]--;
        };
    };

    for (int i = 0; i < 8; i++)
        pg.addPlayer(0, makeTask(0, "A" + to_string(i)));
    for (int i = 0; i < 8; i++)
        pg.addPlayer(1, makeTask(1, "B" + to_string(i)));
    pg.waitAll();

    assert(!violated);
    assert(pg.getInside() == 0);
    cout << "PASSED\n";
}

void testCapacity() {
    cout << "Test 3: Capacity never exceeds 10 ... ";
    Playground pg(10, 15, 15);  // cap=10, perTurn=15, workers=15
    atomic<int> maxSeen{0};

    for (int i = 0; i < 15; i++)
        pg.addPlayer(0, [&pg, &maxSeen]() {
            int cur = pg.getInside();
            int prev = maxSeen.load();
            while (cur > prev && !maxSeen.compare_exchange_weak(prev, cur));
            this_thread::sleep_for(chrono::milliseconds(80));
        });
    pg.waitAll();

    assert(maxSeen <= 10);
    assert(pg.getInside() == 0);
    cout << "PASSED (max occupancy: " << maxSeen << ")\n";
}

void testNoStarvation() {
    cout << "Test 4: All 21 players across 3 teams complete ... ";
    const int NUM_TEAMS = 3;
    Playground pg(10, 5, 10);  // cap=10, perTurn=5, workers=10
    atomic<int> done{0};
    atomic<int> teamInside[NUM_TEAMS];
    for (auto &a : teamInside) a = 0;
    atomic<bool> violated{false};

    auto makeTask = [&](int team, const string &name) {
        return [&, team, name]() {
            teamInside[team]++;
            for (int t = 0; t < NUM_TEAMS; t++)
                if (t != team && teamInside[t] > 0) violated = true;
            this_thread::sleep_for(chrono::milliseconds(playTime(name)));
            teamInside[team]--;
            done++;
        };
    };

    for (int t = 0; t < NUM_TEAMS; t++)
        for (int i = 0; i < 7; i++)
            pg.addPlayer(t, makeTask(t, "T" + to_string(t) + "P" + to_string(i)));
    pg.waitAll();

    assert(done == 21);
    assert(!violated);
    assert(pg.getInside() == 0);
    cout << "PASSED\n";
}

void testRoundRobinFairness() {
    // Team A has 12 players, Team B has 3, perTurn=3
    // Without round-robin, A would run all 12 first, starving B
    // With round-robin: A(3) → B(3) → A(3) → A(3) → A(3)
    // B should complete BEFORE all of A's players finish
    cout << "Test 5: Round-robin fairness — small team not starved by large ... ";
    Playground pg(3, 3, 3);  // cap=3, perTurn=3, workers=3

    atomic<int> aCompleted{0};
    atomic<int> bCompleted{0};
    int aCountWhenBDone = -1;
    mutex checkMtx;

    for (int i = 0; i < 12; i++)
        pg.addPlayer(0, [&]() {
            this_thread::sleep_for(chrono::milliseconds(50));
            aCompleted++;
        });
    for (int i = 0; i < 3; i++)
        pg.addPlayer(1, [&]() {
            this_thread::sleep_for(chrono::milliseconds(50));
            bCompleted++;
            if (bCompleted == 3) {
                lock_guard<mutex> lk(checkMtx);
                if (aCountWhenBDone < 0)
                    aCountWhenBDone = aCompleted.load();
            }
        });

    pg.waitAll();

    // B should finish after A has done at most ~3-6 (one or two turns), not all 12
    assert(aCompleted == 12);
    assert(bCompleted == 3);
    assert(aCountWhenBDone >= 0 && aCountWhenBDone <= 6);
    assert(pg.getInside() == 0);
    cout << "PASSED (A completed " << aCountWhenBDone << " when B finished all 3)\n";
}

void testMultipleTeamsAllComplete() {
    cout << "Test 6: 4 teams interleaved arrivals, all complete ... ";
    const int NUM_TEAMS = 4;
    Playground pg(5, 3, 8);  // cap=5, perTurn=3, workers=8
    atomic<int> completedPerTeam[NUM_TEAMS];
    for (auto &a : completedPerTeam) a = 0;
    atomic<int> teamInside[NUM_TEAMS];
    for (auto &a : teamInside) a = 0;
    atomic<bool> violated{false};

    for (int round = 0; round < 3; round++) {
        for (int t = 0; t < NUM_TEAMS; t++) {
            string name = "R" + to_string(round) + "T" + to_string(t);
            pg.addPlayer(t, [&, t, name]() {
                teamInside[t]++;
                for (int o = 0; o < NUM_TEAMS; o++)
                    if (o != t && teamInside[o] > 0) violated = true;
                this_thread::sleep_for(chrono::milliseconds(playTime(name)));
                teamInside[t]--;
                completedPerTeam[t]++;
            });
        }
    }
    pg.waitAll();

    assert(!violated);
    for (int t = 0; t < NUM_TEAMS; t++) assert(completedPerTeam[t] == 3);
    assert(pg.getInside() == 0);
    cout << "PASSED\n";
}

int main() {
    testSameTeamBasic();
    testNoMixing();
    testCapacity();
    testNoStarvation();
    testRoundRobinFairness();
    testMultipleTeamsAllComplete();
    cout << "\nAll tests passed!\n";
    return 0;
}
