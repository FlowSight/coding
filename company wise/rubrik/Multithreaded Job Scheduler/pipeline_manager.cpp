

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <stdexcept>
#include <cassert>
#include <chrono>

// ─────────────────────────────────────────────
// Given API: Job interface
// ─────────────────────────────────────────────
struct Job {
    std::string jobId;
    std::function<void()> doWork;              // may throw
    std::vector<Job*> children;                // jobs that depend on *this*

    Job(const std::string& id, std::function<void()> work)
        : jobId(id), doWork(std::move(work)) {}
};

// ─────────────────────────────────────────────
// PipelineManager
// ─────────────────────────────────────────────
class PipelineManager {
public:
    // Register a job into the pipeline.
    void addJob(Job* job) {
        jobs_[job->jobId] = job;
    }

    void addDependency(Job* parent, Job* child) {
        parent->children.push_back(child);
    }

    bool execute(int numThreads = 4) {
        // ── Step 1: Build in-degree map ──
        std::unordered_map<std::string, int> inDegree;
        for (auto& [id, job] : jobs_) {
            inDegree.emplace(id, 0);  // ensure every job appears
        }
        for (auto& [id, job] : jobs_) {
            for (Job* child : job->children) {
                inDegree[child->jobId]++;
            }
        }

        // ── Step 2: Shared state protected by mutex ──
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<Job*> readyQueue;
        std::atomic<bool> failed{false};
        int remaining = static_cast<int>(jobs_.size());
        int inFlight  = 0;  // # of jobs currently being executed
        std::string failedJobId;

        // Seed the ready queue with all in-degree-0 jobs (roots).
        for (auto& [id, deg] : inDegree) {
            if (deg == 0) {
                readyQueue.push(jobs_[id]);
            }
        }

        // ── Step 3: Worker loop ──
        // Each worker thread runs this lambda.
        auto workerFn = [&]() {
            while (true) {
                Job* job = nullptr;

                { // critical section: grab a job
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [&]() {
                        return !readyQueue.empty() || remaining == 0 || failed.load();
                    });

                    // Termination conditions
                    if (failed.load() && readyQueue.empty()) return;
                    if (remaining == 0) return;
                    if (readyQueue.empty()) continue; // spurious wakeup

                    job = readyQueue.front();
                    readyQueue.pop();
                    inFlight++;
                }

                // ── Execute the job outside the lock ──
                bool jobFailed = false;
                if (!failed.load()) {
                    try {
                        job->doWork();
                    } catch (const std::exception& e) {
                        jobFailed = true;
                        std::lock_guard<std::mutex> lock(mtx);
                        if (!failed.load()) {
                            failed.store(true);
                            failedJobId = job->jobId;
                            std::cerr << "[FAIL] Job '" << job->jobId
                                      << "' threw: " << e.what() << "\n";
                        }
                    }
                }

                { // critical section: update state after job completion
                    std::lock_guard<std::mutex> lock(mtx);
                    inFlight--;
                    remaining--;

                    if (!jobFailed && !failed.load()) {
                        // Decrement in-degree of children; enqueue newly ready ones.
                        for (Job* child : job->children) {
                            inDegree[child->jobId]--;
                            if (inDegree[child->jobId] == 0) {
                                readyQueue.push(child);
                            }
                        }
                    }
                }
                cv.notify_all();  // wake other threads (new work or termination)
            }
        };

        std::vector<std::thread> pool;
        pool.reserve(numThreads);
        for (int i = 0; i < numThreads; i++) {
            pool.emplace_back(workerFn);
        }

        // ── Step 5: Join all threads ──
        for (auto& t : pool) {
            t.join();
        }

        if (failed.load()) {
            std::cerr << "[PIPELINE] Failed. Triggered by job: "
                      << failedJobId << "\n";
            return false;
        }

        std::cout << "[PIPELINE] All " << jobs_.size()
                  << " jobs completed successfully.\n";
        return true;
    }

private:
    std::unordered_map<std::string, Job*> jobs_;
};


// ─────────────────────────────────────────────
// Helpers / Tests
// ─────────────────────────────────────────────
std::function<void()> makeWork(const std::string& id, int ms, bool shouldFail = false) {
    return [id, ms, shouldFail]() {
        std::cout << "[START] " << id << " (thread "
                  << std::this_thread::get_id() << ")\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        if (shouldFail) {
            throw std::runtime_error("Simulated failure in " + id);
        }
        std::cout << "[DONE]  " << id << "\n";
    };
}

void setupDag(Job& A, Job& B, Job& C, Job& E, Job& F, Job& G,
              Job& K, Job& L, Job& M, PipelineManager& pm) {
    for (auto* j : {&A, &B, &C, &E, &F, &G, &K, &L, &M})
        pm.addJob(j);

    pm.addDependency(&A, &B);
    pm.addDependency(&B, &C);
    pm.addDependency(&C, &G);
    pm.addDependency(&A, &E);
    pm.addDependency(&E, &F);
    pm.addDependency(&F, &G);
    pm.addDependency(&K, &L);
    pm.addDependency(&L, &M);
}

void testAllSucceed() {
    std::cout << "=== Test 1: All jobs succeed ===\n";
    Job A("A", makeWork("A", 100)), B("B", makeWork("B", 150));
    Job C("C", makeWork("C", 100)), E("E", makeWork("E", 200));
    Job F("F", makeWork("F", 100)), G("G", makeWork("G", 50));
    Job K("K", makeWork("K", 80)),  L("L", makeWork("L", 120));
    Job M("M", makeWork("M", 90));

    PipelineManager pm;
    setupDag(A, B, C, E, F, G, K, L, M, pm);

    assert(pm.execute(4));
    std::cout << "\n";
}

void testFailFast() {
    std::cout << "=== Test 2: Job E fails ===\n";
    Job A("A", makeWork("A", 100)), B("B", makeWork("B", 150));
    Job C("C", makeWork("C", 100)), E("E", makeWork("E", 50, true));
    Job F("F", makeWork("F", 100)), G("G", makeWork("G", 50));
    Job K("K", makeWork("K", 80)),  L("L", makeWork("L", 120));
    Job M("M", makeWork("M", 90));

    PipelineManager pm;
    setupDag(A, B, C, E, F, G, K, L, M, pm);

    assert(!pm.execute(4));
    std::cout << "\n";
}

int main() {
    testAllSucceed();
    testFailFast();
    std::cout << "All tests passed.\n";
    return 0;
}
