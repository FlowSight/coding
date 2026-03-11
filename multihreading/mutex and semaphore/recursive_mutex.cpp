/*
 * Multithreaded Factorial (1 to 100) — No duplicate work, NO condition_variable
 *
 * Strategy: Split range [1..100] into chunks across threads.
 *   Thread 0: computes fact[1]  .. fact[25]
 *   Thread 1: computes fact[26] .. fact[50]  (polls until fact[25] is ready)
 *   Thread 2: computes fact[51] .. fact[75]  (polls until fact[50] is ready)
 *   Thread 3: computes fact[76] .. fact[100] (polls until fact[75] is ready)
 *
 * Uses polling (sleep + check) instead of condition_variable.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

const int N = 100;
const int NUM_THREADS = 4;
const long MOD = 1e9 + 7;

long fact[N + 1];
int computedUpTo = 0;       // tracks: fact[0..computedUpTo] are ready
mutex mtx;

void computeChunk(int start, int end, int threadId) {
    // 1. POLL until the previous chunk is done
    while (true) {
        {
            lock_guard<mutex> lk(mtx);
            if (computedUpTo >= start - 1) break;  // dependency ready!
        }
        this_thread::sleep_for(chrono::milliseconds(1));  // poll every 1ms
    }

    // 2. COMPUTE our chunk — no lock needed, we exclusively own [start..end]
    for (int i = start; i <= end; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    cout << "Thread " << threadId << " computed fact[" << start << ".." << end << "]" << endl;

    // 3. SIGNAL that our chunk is done
    {
        lock_guard<mutex> lk(mtx);
        computedUpTo = end;
    }
}

int main() {
    fact[0] = 1;

    int chunkSize = N / NUM_THREADS;

    vector<thread> threads;
    for (int t = 0; t < NUM_THREADS; t++) {
        int start = t * chunkSize + 1;
        int end   = (t == NUM_THREADS - 1) ? N : (t + 1) * chunkSize;
        threads.emplace_back(computeChunk, start, end, t);
    }

    for (auto& th : threads) th.join();

    cout << "\nResults:\n";
    for (int i = 1; i <= N; i++) {
        cout << i << "! = " << fact[i];
        if (i < N) cout << ",  ";
        if (i % 5 == 0) cout << endl;
    }

    return 0;
}