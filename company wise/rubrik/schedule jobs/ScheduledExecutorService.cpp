
#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using Duration = std::chrono::milliseconds;
using Task = std::function<void()>;

struct ScheduledTask {
    TimePoint nextRunTime;
    Task command;
    Duration period;          // 0 means one-shot
    bool fixedRate;           // true = fixedRate, false = fixedDelay
    int id;

    bool operator>(const ScheduledTask& other) const {
        return nextRunTime > other.nextRunTime;
    }
};

class ScheduledExecutorService {
public:
    explicit ScheduledExecutorService(int numThreads = 1)
        : shutdown_(false), taskIdCounter_(0)
    {
        // Start the scheduler thread
        schedulerThread_ = std::thread(&ScheduledExecutorService::schedulerLoop, this);

        // Start worker threads
        for (int i = 0; i < numThreads; ++i) {
            workers_.emplace_back(&ScheduledExecutorService::workerLoop, this);
        }
    }

    ~ScheduledExecutorService() {
        shutdownNow();
    }

    // schedule(Runnable command, long delay, TimeUnit unit)
    // One-shot task that runs after `delay`.
    int schedule(Task command, Duration delay) {
        std::lock_guard<std::mutex> lock(mu_);
        int id = taskIdCounter_++;
        taskQueue_.push({Clock::now() + delay, std::move(command),
                         Duration(0), false, id});
        cv_.notify_one();
        return id;
    }

    // scheduleAtFixedRate(Runnable command, long initialDelay, long period, TimeUnit unit)
    // Periodic task: next run = previous_scheduled_time + period
    // (i.e. drift in execution time does NOT accumulate)
    int scheduleAtFixedRate(Task command, Duration initialDelay, Duration period) {
        std::lock_guard<std::mutex> lock(mu_);
        int id = taskIdCounter_++;
        taskQueue_.push({Clock::now() + initialDelay, std::move(command),
                         period, /*fixedRate=*/true, id});
        cv_.notify_one();
        return id;
    }

    // scheduleWithFixedDelay(Runnable command, long initialDelay, long delay, TimeUnit unit)
    // Periodic task: next run = end_of_previous_execution + delay
    int scheduleWithFixedDelay(Task command, Duration initialDelay, Duration delay) {
        std::lock_guard<std::mutex> lock(mu_);
        int id = taskIdCounter_++;
        taskQueue_.push({Clock::now() + initialDelay, std::move(command),
                         delay, /*fixedRate=*/false, id});
        cv_.notify_one();
        return id;
    }

    void shutdownNow() {
        {
            std::lock_guard<std::mutex> lock(mu_);
            if (shutdown_) return;
            shutdown_ = true;
        }
        cv_.notify_all();
        workCv_.notify_all();

        if (schedulerThread_.joinable()) schedulerThread_.join();
        for (auto& w : workers_) {
            if (w.joinable()) w.join();
        }
    }

private:
    // Min-heap of tasks ordered by nextRunTime
    std::priority_queue<ScheduledTask, std::vector<ScheduledTask>,
                        std::greater<ScheduledTask>> taskQueue_;

    // Ready-to-run tasks dispatched to worker threads
    std::queue<ScheduledTask> readyQueue_;

    std::mutex mu_;
    std::condition_variable cv_;       // for scheduler thread
    std::condition_variable workCv_;   // for worker threads

    std::thread schedulerThread_;
    std::vector<std::thread> workers_;

    std::atomic<bool> shutdown_;
    int taskIdCounter_;

    void schedulerLoop() {
        std::unique_lock<std::mutex> lock(mu_);
        while (!shutdown_) {
            if (taskQueue_.empty()) {
                cv_.wait(lock, [&] { return shutdown_ || !taskQueue_.empty(); });
                continue;
            }

            auto nextTime = taskQueue_.top().nextRunTime;
            if (cv_.wait_until(lock, nextTime, [&] {
                    return shutdown_ ||
                           (!taskQueue_.empty() && taskQueue_.top().nextRunTime <= Clock::now());
                }))
            {
                if (shutdown_) break;
                ScheduledTask task = taskQueue_.top();
                taskQueue_.pop();

                readyQueue_.push(task);
                workCv_.notify_one();
            }
            // If we woke up spuriously or a new earlier task was added, loop again
        }
    }

    void workerLoop() {
        while (true) {
            ScheduledTask task;
            {
                std::unique_lock<std::mutex> lock(mu_);
                workCv_.wait(lock, [&] {
                    return shutdown_ || !readyQueue_.empty();
                });
                if (shutdown_ && readyQueue_.empty()) return;

                task = readyQueue_.front();
                readyQueue_.pop();
            }

            // Execute outside the lock
            task.command(); 
            auto finishTime = Clock::now();

            // Re-schedule periodic tasks
            if (task.period.count() > 0) {
                std::lock_guard<std::mutex> lock(mu_);
                if (!shutdown_) {
                    if (task.fixedRate) {
                        // Fixed rate: next = previous_scheduled + period
                        task.nextRunTime = task.nextRunTime + task.period;
                        // If we're already past the next scheduled time, run immediately
                        if (task.nextRunTime < Clock::now())
                            task.nextRunTime = Clock::now();
                    } else {
                        // Fixed delay: next = end_of_execution + delay
                        task.nextRunTime = finishTime + task.period;
                    }
                    taskQueue_.push(task);
                    cv_.notify_one();
                }
            }
        }
    }
};

// ──────────────────────── Demo ────────────────────────

int main() {
    std::cout << "=== ScheduledExecutorService Demo ===\n\n";

    ScheduledExecutorService executor(2);

    auto now = [] {
        static auto start = Clock::now();
        auto ms = std::chrono::duration_cast<Duration>(Clock::now() - start).count();
        return ms;
    };

    // 1) One-shot task after 500ms
    executor.schedule([&] {
        std::cout << "[" << now() << "ms] One-shot task executed\n";
    }, Duration(500));

    // 2) Fixed-rate: every 300ms after initial 200ms delay
    executor.scheduleAtFixedRate([&] {
        std::cout << "[" << now() << "ms] Fixed-rate task executed\n";
        std::this_thread::sleep_for(Duration(50)); // simulate work
    }, Duration(200), Duration(300));

    // 3) Fixed-delay: 400ms between end of one execution and start of next,
    //    initial delay 100ms
    executor.scheduleWithFixedDelay([&] {
        std::cout << "[" << now() << "ms] Fixed-delay task executed\n";
        std::this_thread::sleep_for(Duration(100)); // simulate work
    }, Duration(100), Duration(400));

    // Let it run for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "\nShutting down...\n";
    executor.shutdownNow();
    std::cout << "Done.\n";

    return 0;
}