/*
 * Semaphore Demo (C++20)
 *
 * A semaphore is a counter that limits how many threads can access
 * a resource at the same time.
 *
 *   acquire() → counter > 0? decrement & proceed. counter == 0? BLOCK.
 *   release() → increment counter, wake one blocked thread.
 *
 * Key difference from mutex:
 *   - mutex: 1 thread at a time, must unlock from same thread
 *   - semaphore: N threads at a time, ANY thread can release
 *
 * Compile: g++ -std=c++20 semaphore.cpp -o semaphore && ./semaphore
 */

#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

using namespace std;

// ─── Example 1: Limit concurrency (like a connection pool) ───

counting_semaphore<3> pool(3);  // max 3 threads at a time

void dbQuery(int id) {
    pool.acquire();   // get a "connection" (blocks if all 3 in use)

    cout << "Thread " << id << " querying DB...\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Thread " << id << " done.\n";

    pool.release();   // return the "connection"
}

// ─── Example 2: Signaling between threads (producer → consumer) ───

binary_semaphore ready(0);  // starts at 0 = nothing ready
int sharedData = 0;

void producer() {
    this_thread::sleep_for(chrono::milliseconds(300));
    sharedData = 42;
    cout << "Producer: data ready!\n";
    ready.release();   // signal consumer (0 → 1)
}

void consumer() {
    cout << "Consumer: waiting for data...\n";
    ready.acquire();   // blocks until producer signals (1 → 0)
    cout << "Consumer: got " << sharedData << "\n";
}

int main() {
    cout << "=== Connection Pool (max 3 concurrent) ===\n";
    {
        vector<thread> threads;
        for (int i = 0; i < 8; i++)
            threads.emplace_back(dbQuery, i);
        for (auto& t : threads) t.join();
    }

    cout << "\n=== Producer-Consumer Signaling ===\n";
    {
        thread t1(consumer);
        thread t2(producer);
        t1.join();
        t2.join();
    }

    return 0;
}
