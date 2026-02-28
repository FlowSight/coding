/*
 * Latch Demo — something a barrier CAN'T do
 *
 * Scenario: Main thread waits for 3 workers to finish loading data,
 *           but workers DON'T wait for each other — they count_down and exit.
 *
 * Why barrier can't do this:
 *   barrier.arrive_and_wait() → ALL participants must call it (blocks each one).
 *   If a worker just wants to signal "I'm done" and leave, barrier forces it to wait.
 *
 * Latch allows: count_down() without blocking — fire and forget.
 *   Only the main thread calls wait() to block until counter == 0.
 */

#include <iostream>
#include <thread>
#include <latch>
#include <vector>
#include <chrono>

using namespace std;

latch allLoaded(3);   // main waits until 3 workers signal done

void loadData(int id, int loadTimeMs) {
    // Simulate loading data
    cout << "Worker " << id << " loading...\n";
    this_thread::sleep_for(chrono::milliseconds(loadTimeMs));
    cout << "Worker " << id << " done loading!\n";

    allLoaded.count_down();  // signal "I'm done" — does NOT block!

    // Worker keeps doing OTHER work — doesn't wait for anyone
    cout << "Worker " << id << " doing independent cleanup...\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Worker " << id << " fully exited.\n";
}

int main() {
    vector<thread> workers;
    workers.emplace_back(loadData, 0, 500);
    workers.emplace_back(loadData, 1, 200);
    workers.emplace_back(loadData, 2, 800);

    // Main thread blocks here until ALL 3 workers have called count_down()
    allLoaded.wait();

    // Guaranteed: all data is loaded. Workers may still be doing cleanup above.
    cout << "\n>>> Main: All data loaded! Starting processing...\n\n";

    for (auto& t : workers) t.join();
    return 0;
}
