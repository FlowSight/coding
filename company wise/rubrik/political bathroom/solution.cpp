#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <numeric>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
using namespace std;

class Bathroom {
public:
    enum class Party { NONE, D, R };

    Bathroom(int cap = 3) : capacity(cap) {}

    long long arrive(Party p) {
        unique_lock<mutex> lock(mtx);
        long long t = nextTicket++;
        if (p == Party::D) dQ.push(t);
        else rQ.push(t);
        cvD.notify_all();
        cvR.notify_all();
        return t;
    }

    void enter(Party p, long long myTicket) {
        unique_lock<mutex> lock(mtx);
        auto &cv = (p == Party::D ? cvD : cvR);
        cv.wait(lock, [&]() { return canEnter(p, myTicket); });

        if (p == Party::D) dQ.pop();
        else rQ.pop();

        if (current == Party::NONE) current = p;
        inside++;
    }

    void leave(Party p) {
        unique_lock<mutex> lock(mtx);
        (void)p;
        inside--;
        if (inside == 0) {
            current = Party::NONE;
            cvD.notify_all();
            cvR.notify_all();
        } else {
            if (current == Party::D) cvD.notify_all();
            else if (current == Party::R) cvR.notify_all();
        }
    }

    // Expose state for testing
    int getInside() { lock_guard<mutex> lk(mtx); return inside; }
    Party getCurrent() { lock_guard<mutex> lk(mtx); return current; }

private:
    int capacity;
    int inside = 0;
    Party current = Party::NONE;
    long long nextTicket = 0;

    queue<long long> dQ, rQ;
    mutex mtx;
    condition_variable cvD, cvR;

    bool canEnter(Party p, long long myTicket) {
        if (inside >= capacity) return false;
        if (current != Party::NONE && current != p) return false;

        if (p == Party::D) {
            if (dQ.empty() || dQ.front() != myTicket) return false;
        } else {
            if (rQ.empty() || rQ.front() != myTicket) return false;
        }

        if (current == p) return true;

        if (current == Party::NONE) {
            if (p == Party::D) {
                if (rQ.empty()) return true;
                return dQ.front() < rQ.front();
            } else {
                if (dQ.empty()) return true;
                return rQ.front() < dQ.front();
            }
        }
        return false;
    }
};

// ---------- helpers for tests ----------
using Party = Bathroom::Party;

int f(const string &name) {
    return 1 + (accumulate(name.begin(), name.end(), 0) % 3);
}

void person(Bathroom &b, Party p, const string &name) {
    long long ticket = b.arrive(p);
    b.enter(p, ticket);
    this_thread::sleep_for(chrono::milliseconds(f(name) * 100)); // speed up for tests
    b.leave(p);
}

// ---------- test cases ----------
void testBasicSameParty() {
    cout << "Test 1: 3 Democrats enter together ... ";
    Bathroom b;
    vector<thread> threads;
    for (int i = 0; i < 3; i++)
        threads.emplace_back(person, ref(b), Party::D, "D" + to_string(i));
    for (auto &t : threads) t.join();
    assert(b.getInside() == 0);
    assert(b.getCurrent() == Party::NONE);
    cout << "PASSED\n";
}

void testNoMixing() {
    cout << "Test 2: No mixed occupancy ... ";
    Bathroom b;
    // Track who is inside at any moment
    atomic<int> dInside{0}, rInside{0};
    atomic<bool> violated{false};

    auto go = [&](Party p, const string &name) {
        long long ticket = b.arrive(p);
        b.enter(p, ticket);
        if (p == Party::D) dInside++;
        else rInside++;

        // Check invariant: never both parties inside
        if (dInside > 0 && rInside > 0) violated = true;

        this_thread::sleep_for(chrono::milliseconds(f(name) * 100));

        if (p == Party::D) dInside--;
        else rInside--;
        b.leave(p);
    };

    vector<thread> threads;
    for (int i = 0; i < 5; i++)
        threads.emplace_back(go, Party::D, "D" + to_string(i));
    for (int i = 0; i < 5; i++)
        threads.emplace_back(go, Party::R, "R" + to_string(i));
    for (auto &t : threads) t.join();

    assert(!violated);
    assert(b.getInside() == 0);
    cout << "PASSED\n";
}

void testCapacityNotExceeded() {
    cout << "Test 3: Capacity never exceeds 3 ... ";
    Bathroom b;
    atomic<int> maxSeen{0};

    auto go = [&](Party p, const string &name) {
        long long ticket = b.arrive(p);
        b.enter(p, ticket);
        int cur = b.getInside();
        int prev = maxSeen.load();
        while (cur > prev && !maxSeen.compare_exchange_weak(prev, cur));

        this_thread::sleep_for(chrono::milliseconds(f(name) * 100));
        b.leave(p);
    };

    vector<thread> threads;
    // 6 same-party to stress capacity
    for (int i = 0; i < 6; i++)
        threads.emplace_back(go, Party::D, "D" + to_string(i));
    for (auto &t : threads) t.join();

    assert(maxSeen <= 3);
    assert(b.getInside() == 0);
    cout << "PASSED (max occupancy seen: " << maxSeen << ")\n";
}

void testAllComplete() {
    cout << "Test 4: All 10 people eventually complete (no starvation) ... ";
    Bathroom b;
    atomic<int> done{0};

    auto go = [&](Party p, const string &name) {
        long long ticket = b.arrive(p);
        b.enter(p, ticket);
        this_thread::sleep_for(chrono::milliseconds(f(name) * 100));
        b.leave(p);
        done++;
    };

    vector<thread> threads;
    for (int i = 0; i < 5; i++)
        threads.emplace_back(go, Party::D, "D" + to_string(i));
    for (int i = 0; i < 5; i++)
        threads.emplace_back(go, Party::R, "R" + to_string(i));
    for (auto &t : threads) t.join();

    assert(done == 10);
    cout << "PASSED\n";
}

void runTests() {
    testBasicSameParty();
    testNoMixing();
    testCapacityNotExceeded();
    testAllComplete();
    cout << "\nAll tests passed!\n";
}

int main() {
    runTests();
    return 0;
}
