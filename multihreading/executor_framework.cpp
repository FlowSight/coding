/*
 * Executor Framework in C++ (mirrors Java's ExecutorService)
 *
 * Java equivalent:
 *   ExecutorService pool = Executors.newFixedThreadPool(4);
 *   Future<int> f = pool.submit(() -> compute());
 *   int result = f.get();
 *   pool.shutdown();
 *   pool.awaitTermination();
 *
 * Components:
 *   1. ThreadPool        → manages N worker threads + task queue
 *   2. submit(task)      → returns std::future<T> (like Java's Future)
 *   3. shutdown()        → stop accepting, finish pending tasks
 *   4. awaitTermination()→ block until all tasks done
 *
 * C++ tools used:
 *   std::future / std::promise  → async result passing
 *   std::packaged_task          → wraps callable + gives a future
 *   std::function               → type-erased task in the queue
 *
 * Compile: g++ -std=c++14 executor_framework.cpp -o executor_framework && ./executor_framework
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <chrono>
#include <stdexcept>

using namespace std;

// ─── ThreadPoolExecutor ───

class ThreadPoolExecutor {
public:
    explicit ThreadPoolExecutor(int numThreads) : _shutdown(false) {
        for (int i = 0; i < numThreads; i++) {
            _workers.emplace_back([this] { workerLoop(); });
        }
        cout << "Pool created with " << numThreads << " threads\n";
    }

    template <typename F, typename... Args>
    auto submit(F&& func, Args&&... args) -> future<decltype(func(args...))> {
        using ReturnType = decltype(func(args...));

        if (_shutdown) {
            throw runtime_error("Cannot submit — pool is shut down");
        }

        // packaged_task wraps the callable and gives us a future
        auto task = make_shared<packaged_task<ReturnType()>>(
            bind(forward<F>(func), forward<Args>(args)...)
        );

        future<ReturnType> result = task->get_future();

        {
            lock_guard<mutex> lk(_mtxQueue);
            // Push a void() wrapper into the queue
            _tasks.push([task]() { (*task)(); });
        }
        _cvQueue.notify_one();  // wake a worker

        return result;
    }

    void execute(function<void()> task) {
        if (_shutdown) {
            throw runtime_error("Cannot execute — pool is shut down");
        }
        {
            lock_guard<mutex> lk(_mtxQueue);
            _tasks.push(move(task));
        }
        _cvQueue.notify_one();
    }

    void shutdown() {
        {
            lock_guard<mutex> lk(_mtxQueue);
            _shutdown = true;
        }
        _cvQueue.notify_all();  // wake all workers to check shutdown
        cout << "Pool shutting down...\n";
    }

    void awaitTermination() {
        for (auto& w : _workers) {
            if (w.joinable()) w.join();
        }
        cout << "All workers terminated.\n";
    }

    ~ThreadPoolExecutor() {
        if (!_shutdown) shutdown();
        awaitTermination();
    }

private:
    void workerLoop() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lk(_mtxQueue);
                _cvQueue.wait(lk, [this] {
                    return _shutdown || !_tasks.empty();
                });

                // If shutdown AND no more tasks → exit
                if (_shutdown && _tasks.empty()) return;

                task = move(_tasks.front());
                _tasks.pop();
            }
            try {
                task();  // run outside the lock
            } catch (const exception& e) {
                cerr << "Task threw: " << e.what() << "\n";
            }
        }
    }

    vector<thread> _workers;
    queue<function<void()>> _tasks;
    mutex _mtxQueue;
    condition_variable _cvQueue;
    bool _shutdown;
};

// ─── Demo ───

int heavyComputation(int x) {
    this_thread::sleep_for(chrono::milliseconds(500));
    return x * x;
}

string fetchData(const string& url) {
    this_thread::sleep_for(chrono::milliseconds(300));
    return "data from " + url;
}

int main() {
    // Like Java: ExecutorService pool = Executors.newFixedThreadPool(3);
    ThreadPoolExecutor pool(3);

    // ── submit() with return values (like Java Future) ──
    cout << "\n=== Submit with Futures ===\n";

    auto f1 = pool.submit(heavyComputation, 5);
    auto f2 = pool.submit(heavyComputation, 10);
    auto f3 = pool.submit(fetchData, "api.example.com");
    auto f4 = pool.submit([] { return 7 + 35; });  // lambda

    // Do other work while tasks run...
    cout << "Tasks submitted, doing other work...\n";
    this_thread::sleep_for(chrono::milliseconds(100));

    // .get() blocks until result is ready (like Java's future.get())
    cout << "5² = " << f1.get() << "\n";
    cout << "10² = " << f2.get() << "\n";
    cout << "Fetch: " << f3.get() << "\n";
    cout << "Lambda: " << f4.get() << "\n";

    // ── execute() fire-and-forget (like Java's pool.execute()) ──
    cout << "\n=== Execute (fire & forget) ===\n";

    for (int i = 0; i < 5; i++) {
        pool.execute([i] {
            cout << "Task " << i << " on thread "
                 << this_thread::get_id() << "\n";
            this_thread::sleep_for(chrono::milliseconds(200));
        });
    }

    // ── shutdown + await (like Java) ──
    pool.shutdown();          // no more tasks accepted
    pool.awaitTermination();  // wait for all tasks to finish

    return 0;
}
