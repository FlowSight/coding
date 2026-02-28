/*
 * Example: 3 runners in a relay race with 3 legs.
 *   - Each runner finishes their leg at different times.
 *   - All must finish leg 1 before anyone starts leg 2.
 *
 * Implementation: counter + mutex + condition_variable
 *   - Each thread decrements counter on arrival
 *   - Last thread to arrive (counter == 0) wakes everyone
 *   - Counter resets for the next phase
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

class Barrier {
public:
    explicit Barrier(int count)
        : _totalThreads(count), _waiting(0), _phase(0) {}

    void arrive_and_wait() {
        unique_lock<mutex> lk(_mtx);
        int curPhase = _phase;       // remember which phase we're in

        _waiting++;

        if (_waiting == _totalThreads) {
            // Last thread to arrive — release everyone
            _waiting = 0;
            _phase++;                // move to next phase so barrier is reusable
            _cv.notify_all();
        } else {
            // Not everyone is here yet — sleep until phase changes
            _cv.wait(lk, [&] { return _phase != curPhase; });
        }
    }

private:
    int _totalThreads;
    int _waiting;
    int _phase;                      // increments each time barrier is released
    mutex _mtx;
    condition_variable _cv;
};


Barrier bar(3);

void worker(int id) {
    // Phase 1
    this_thread::sleep_for(chrono::milliseconds(100 * (id + 1)));  // simulate work
    cout << "Thread " << id << " finished phase 1\n";
    bar.arrive_and_wait();
    // ─── barrier: all threads finished phase 1 ───

    // Phase 2
    this_thread::sleep_for(chrono::milliseconds(100 * (3 - id)));
    cout << "Thread " << id << " finished phase 2\n";
    bar.arrive_and_wait();
    // ─── barrier: all threads finished phase 2 ───

    // Phase 3
    cout << "Thread " << id << " finished phase 3\n";
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < 3; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) t.join();

    cout << "\nAll phases complete!\n";
    return 0;
}
