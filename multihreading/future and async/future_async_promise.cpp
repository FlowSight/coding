
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

int heavyWork(int x) {
    cout << "  [computing on thread " << this_thread::get_id() << "]\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    return x * x;
}

int main() {

    // ═══════════════════════════════════════════
    // 1. std::async — simplest way
    // ═══════════════════════════════════════════
    cout << "=== async + future ===\n";
    {
        // launch::async  → guarantees a new thread
        // launch::deferred → runs lazily when you call .get()
        // default (async | deferred) → implementation decides

        future<int> f = async(launch::async, heavyWork, 5);

        cout << "Task launched, doing other stuff...\n";
        // f.get() blocks until the result is ready
        int result = f.get();
        cout << "5² = " << result << "\n";
        // Note: .get() can only be called ONCE. Second call = undefined behavior.
    }

    // ═══════════════════════════════════════════
    // 2. std::promise + std::future — manual control
    // ═══════════════════════════════════════════
    cout << "\n=== promise + future ===\n";
    {
        promise<int> p;                   // writer side
        future<int> f = p.get_future();   // reader side (linked to this promise)

        // Producer thread: computes and sets the value
        thread producer([&p] {
            cout << "  Producer working...\n";
            this_thread::sleep_for(chrono::milliseconds(500));
            p.set_value(42);   // "here's your answer"
            cout << "  Producer: value sent!\n";
        });

        // Consumer (main thread): waits for the value
        cout << "Waiting for result...\n";
        int result = f.get();         // blocks until set_value()
        cout << "Got: " << result << "\n";

        producer.join();
    }

    // ═══════════════════════════════════════════
    // 2b. promise — passing exceptions across threads
    // ═══════════════════════════════════════════
    cout << "\n=== promise with exception ===\n";
    {
        promise<int> p;
        future<int> f = p.get_future();

        thread t([&p] {
            try {
                throw runtime_error("something went wrong!");
                p.set_value(99);   // never reached
            } catch (...) {
                p.set_exception(current_exception());  // send the exception
            }
        });

        try {
            int val = f.get();    // this throws the exception from the other thread!
            cout << val << "\n";
        } catch (const exception& e) {
            cout << "Caught from other thread: " << e.what() << "\n";
        }

        t.join();
    }

    // ═══════════════════════════════════════════
    // 3. std::packaged_task — callable wrapper + future
    // ═══════════════════════════════════════════
    cout << "\n=== packaged_task ===\n";
    {
        // Wrap the function — doesn't run it yet!
        packaged_task<int(int)> task(heavyWork);
        future<int> f = task.get_future();

        // You decide when to run it:
        // Option A: on a thread
        thread t(move(task), 7);   // move because packaged_task is not copyable

        cout << "Task given to thread...\n";
        int result = f.get();
        cout << "7² = " << result << "\n";

        t.join();
    }

    // ═══════════════════════════════════════════
    // 3b. packaged_task — run without thread (deferred)
    // ═══════════════════════════════════════════
    cout << "\n=== packaged_task (no thread) ===\n";
    {
        packaged_task<int(int)> task(heavyWork);
        future<int> f = task.get_future();

        // Just call it directly — runs on current thread
        task(9);

        cout << "9² = " << f.get() << "\n";
    }

    // ═══════════════════════════════════════════
    // Comparison: which to use?
    // ═══════════════════════════════════════════
    /*
     * ┌──────────────────┬──────────────────────────────────────────┐
     * │ Tool             │ When to use                              │
     * ├──────────────────┼──────────────────────────────────────────┤
     * │ async + future   │ Simple "run this, get result" — default  │
     * │                  │ choice. Manages thread for you.          │
     * ├──────────────────┼──────────────────────────────────────────┤
     * │ promise + future │ When the producing thread decides what   │
     * │                  │ to send (value OR exception). Manual     │
     * │                  │ control over when the value is set.      │
     * ├──────────────────┼──────────────────────────────────────────┤
     * │ packaged_task    │ When you want to wrap a callable and     │
     * │                  │ run it later (e.g., in a thread pool     │
     * │                  │ queue). Bridges callable → future.       │
     * └──────────────────┴──────────────────────────────────────────┘
     *
     * Internally:  async uses packaged_task uses promise.
     *   async → creates packaged_task → packaged_task creates promise → promise creates future
     */

    return 0;
}
