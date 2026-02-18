/*
 * Simplified Executor Service (Thread Pool) - All in one file
 *
 *
 * Key Idea:
 *   - A pool of N worker threads is created upfront.
 *   - You "submit" tasks (any void() callable) into a shared queue.
 *   - Worker threads pick tasks from the queue and execute them.
 *   - You can wait for all tasks to finish, then shut down.
 *
 * Synchronization primitives used:
 *   mutex              – protects shared data (task queue, running counter)
 *   condition_variable – lets threads sleep until there's work (or shutdown)
 *   unique_lock        – RAII wrapper for locking/unlocking a mutex
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>   // std::function
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>


class ExecService {
public:
    using Task = std::function<void()>;

    explicit ExecService(int n) : numThreads_(n), taskRunning_(0), shutdown_(false) {
        workers_.reserve(n);
        for (int i = 0; i < n; ++i) {
            workers_.emplace_back(&ExecService::workerLoop, this);
        }
    }

    // Prevent copying / moving (threads aren't copyable)
    ExecService(const ExecService&)            = delete;
    ExecService& operator=(const ExecService&) = delete;

    void submit(Task task) {
        {
            // important pattern
            std::unique_lock<std::mutex> lk(mtxQueue_);
            pendingTasks_.push(std::move(task));
        }
        cvQueue_.notify_one();
    }

    void waitTaskDone() {
        for (;;) {
            std::unique_lock<std::mutex> lkQ(mtxQueue_);

            if (pendingTasks_.empty()) {
                // Queue is empty — now also wait for running tasks to finish
                std::unique_lock<std::mutex> lkR(mtxRunning_);
                cvRunning_.wait(lkR, [&] { return taskRunning_ <= 0; });
                break;   // nothing pending, nothing running → all done
            } else {
                // Release the queue lock before sleeping, otherwise
                // workers can't grab tasks while we're sleeping!
                lkQ.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    // ── Shut down the pool (discards pending tasks, joins threads) ──
    void shutdown() {
        {
            std::unique_lock<std::mutex> lk(mtxQueue_);
            shutdown_ = true;
            // Discard any remaining tasks
            std::queue<Task>().swap(pendingTasks_);
        }
        // Wake ALL workers so they see shutdown_ == true and exit
        cvQueue_.notify_all();

        for (auto& t : workers_) {
            if (t.joinable()) t.join();
        }
        workers_.clear();
    }

    ~ExecService() {
        if (!workers_.empty()) shutdown();
    }

private:

    void workerLoop() {
        Task task;

        for (;;) {
            {
                std::unique_lock<std::mutex> lk(mtxQueue_);
                // VERY IMP : instea of doing busy waiting..conditional var is used
                cvQueue_.wait(lk, [&] {
                    return shutdown_ || !pendingTasks_.empty();
                });

                if (shutdown_) return; 
                task = std::move(pendingTasks_.front());
                pendingTasks_.pop();

                {
                    std::unique_lock<std::mutex> lkR(mtxRunning_);
                    ++taskRunning_;
                }
            }

            // 3. EXECUTE the task (no locks held — tasks run concurrently)
            try {
                task();
            } catch (...) {
                // Task threw — swallow the exception but still
                // decrement the counter so waitTaskDone() doesn't hang.
            }

            {
                std::unique_lock<std::mutex> lkR(mtxRunning_);
                --taskRunning_;
                if (taskRunning_ == 0) {
                    cvRunning_.notify_one();
                }
            }
        }
    }

    int                          numThreads_;
    std::vector<std::thread>     workers_;

    std::queue<Task>             pendingTasks_;  // tasks waiting to run
    std::mutex                   mtxQueue_;      // guards pendingTasks_
    std::condition_variable      cvQueue_;       // "new task available" signal

    int                          taskRunning_;   // how many tasks are executing right now
    std::mutex                   mtxRunning_;    // guards taskRunning_
    std::condition_variable      cvRunning_;     // "a task just finished" signal

    volatile bool                shutdown_;      // tells workers to exit
};


// Way 1 — plain function
void doTask() {
    std::cout << "Hello from a plain function\n";
}

// Way 2 — functor (a class with operator())
struct MyFunctor {
    void operator()() {
        std::cout << "Hello from a functor\n";
    }
};

int main() {
    // Create a thread pool with 2 worker threads
    ExecService pool(2);

    // Way 3 — lambda
    pool.submit([] {
        std::cout << "Hello from a lambda\n";
    });

    pool.submit(&doTask);          // submit the plain function
    pool.submit(MyFunctor());      // submit the functor

    // Wait for all submitted tasks to finish
    pool.waitTaskDone();

    // Cleanly shut down (joins worker threads)
    pool.shutdown();

    return 0;
}
