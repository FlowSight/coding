/*
 * CSV Copy: Efficient large-file copy using read()/write() APIs
 *
 * Design:
 *   1 Reader thread  — read() may not be thread-safe, so single reader is safest
 *   N Writer threads  — write() IS thread-safe and atomic
 *   Bounded queue     — backpressure to cap memory usage
 *
 * Follow-ups addressed:
 *   (1) Ordering:   sequence numbers + reorder buffer in a dedicated flush thread
 *   (2) Batching:   size-based batching (not count-based) to handle skew
 *   (3) Memory:     bounded queue + batch size cap
 *   (4) Large rows: a single oversized row becomes its own batch
 *   (5) Throughput: pipelining — reader, writers, flusher all run concurrently
 */

#include <bits/stdc++.h>
using namespace std;

// ===================== Mock APIs =====================
// Returns (row_id, row_data). nullopt when EOF.
optional<pair<int, string>> readRow() {
    return nullopt; // assume implemented externally
}

// Writes a batch atomically: header, rows..., footer. Thread-safe.
void writeBatch(const vector<string>& batch) {
    // assume implemented externally
}


// =====================================================================
//  Bounded thread-safe queue (reusable)
// =====================================================================
template <typename T>
class BoundedQueue {
    queue<T>           q_;
    mutex              mtx_;
    condition_variable cv_not_empty_, cv_not_full_;
    size_t             max_size_;
    bool               closed_ = false;

public:
    explicit BoundedQueue(size_t max_size) : max_size_(max_size) {}

    void push(T item) {
        unique_lock<mutex> lk(mtx_);
        cv_not_full_.wait(lk, [&] { return q_.size() < max_size_; });
        q_.push(move(item));
        lk.unlock();
        cv_not_empty_.notify_one();
    }

    // Returns false when queue is closed AND empty (no more data).
    bool pop(T& out) {
        unique_lock<mutex> lk(mtx_);
        cv_not_empty_.wait(lk, [&] { return !q_.empty() || closed_; });
        if (q_.empty() && closed_) return false;
        out = move(q_.front());
        q_.pop();
        lk.unlock();
        cv_not_full_.notify_all();
        return true;
    }

    // Drain up to max_bytes worth of items. Returns false when done.
    // Uses sizeFn(item) to measure each item's byte size.
    template <typename SizeFn>
    bool drain_batch(vector<T>& batch, size_t max_bytes, SizeFn sizeFn) {
        batch.clear();
        size_t bytes = 0;

        unique_lock<mutex> lk(mtx_);
        cv_not_empty_.wait(lk, [&] { return !q_.empty() || closed_; });
        if (q_.empty() && closed_) return false;

        while (!q_.empty() && bytes + sizeFn(q_.front()) <= max_bytes) {
            bytes += sizeFn(q_.front());
            batch.push_back(move(q_.front()));
            q_.pop();
        }
        // Handle single row > max_bytes (large-row follow-up)
        if (batch.empty() && !q_.empty()) {
            batch.push_back(move(q_.front()));
            q_.pop();
        }
        lk.unlock();
        cv_not_full_.notify_all();
        return true;
    }

    void close() {
        lock_guard<mutex> lk(mtx_);
        closed_ = true;
        cv_not_empty_.notify_all();
    }
};


// =====================================================================
//  VERSION 1 — Order does NOT matter
//  Reader → BoundedQueue → N Writers (each grabs a batch and writes)
// =====================================================================
class UnorderedCopier {
    static constexpr int    NUM_WRITERS     = 4;
    static constexpr size_t MAX_QUEUE_SIZE  = 1024;
    static constexpr size_t MAX_BATCH_BYTES = 1 * 1024 * 1024;

    BoundedQueue<string> queue_;
    thread               reader_thread_;
    vector<thread>       writer_threads_;

    void readerLoop() {
        while (true) {
            auto res = readRow();
            if (!res) break;
            queue_.push(move(res->second));
        }
        queue_.close();
    }

    void writerLoop() {
        vector<string> batch;
        auto sizeFn = [](const string& s) { return s.size(); };

        while (queue_.drain_batch(batch, MAX_BATCH_BYTES, sizeFn)) {
            if (!batch.empty()) writeBatch(batch);
        }
    }

public:
    UnorderedCopier() : queue_(MAX_QUEUE_SIZE) {}

    void run() {
        reader_thread_ = thread(&UnorderedCopier::readerLoop, this);
        for (int i = 0; i < NUM_WRITERS; i++)
            writer_threads_.emplace_back(&UnorderedCopier::writerLoop, this);

        reader_thread_.join();
        for (auto& w : writer_threads_) w.join();
    }
};


// =====================================================================
//  VERSION 2b — Order preserved, SIMPLER (single writer + reorder buf)
//  Good starting point in an interview.
//  Reader → BoundedQueue<(seq, row)> → 1 Writer with reorder map
// =====================================================================
class OrderedSimpleCopier {
    static constexpr size_t MAX_QUEUE_SIZE  = 1024;
    static constexpr size_t MAX_BATCH_BYTES = 1 * 1024 * 1024;

    using TaggedRow = pair<int, string>;

    BoundedQueue<TaggedRow> queue_;
    thread                  reader_thread_;
    thread                  writer_thread_;

    void readerLoop() {
        while (true) {
            auto res = readRow();
            if (!res) break;
            queue_.push(move(*res));
        }
        queue_.close();
    }

    void writerLoop() {
        map<int, string> reorder;
        int next_seq = 0;

        TaggedRow item;
        while (queue_.pop(item)) {
            reorder[item.first] = move(item.second);

            // Flush all consecutive rows starting from next_seq
            vector<string> batch;
            size_t batch_bytes = 0;

            while (reorder.count(next_seq)) {
                size_t row_sz = reorder[next_seq].size();
                if (!batch.empty() && batch_bytes + row_sz > MAX_BATCH_BYTES) {
                    writeBatch(batch);
                    batch.clear();
                    batch_bytes = 0;
                }
                batch_bytes += row_sz;
                batch.push_back(move(reorder[next_seq]));
                reorder.erase(next_seq);
                next_seq++;
            }
            if (!batch.empty()) writeBatch(batch);
        }

        // Flush any remaining buffered rows
        vector<string> batch;
        size_t batch_bytes = 0;
        while (reorder.count(next_seq)) {
            size_t row_sz = reorder[next_seq].size();
            if (!batch.empty() && batch_bytes + row_sz > MAX_BATCH_BYTES) {
                writeBatch(batch);
                batch.clear();
                batch_bytes = 0;
            }
            batch_bytes += row_sz;
            batch.push_back(move(reorder[next_seq]));
            reorder.erase(next_seq);
            next_seq++;
        }
        if (!batch.empty()) writeBatch(batch);
    }

public:
    OrderedSimpleCopier() : queue_(MAX_QUEUE_SIZE) {}

    void run() {
        reader_thread_ = thread(&OrderedSimpleCopier::readerLoop, this);
        writer_thread_  = thread(&OrderedSimpleCopier::writerLoop, this);
        reader_thread_.join();
        writer_thread_.join();
    }
};


// =====================================================================
//  VERSION 2 — Order preserved, MAX throughput
//  Reader → BoundedQueue → N Workers → ReorderBuffer → 1 Flusher
// =====================================================================
class OrderedCopier {
    static constexpr int    NUM_WORKERS     = 4;
    static constexpr size_t MAX_QUEUE_SIZE  = 1024;
    static constexpr size_t MAX_BATCH_BYTES = 1 * 1024 * 1024;

    using TaggedRow = pair<int, string>;

    // Reader → Workers queue
    BoundedQueue<TaggedRow> queue_;

    // Workers → Flusher reorder buffer
    mutex                    flush_mtx_;
    condition_variable       flush_cv_;
    map<int, string>         flush_buf_;
    atomic<int>              active_workers_{NUM_WORKERS};

    thread                   reader_thread_;
    vector<thread>           worker_threads_;
    thread                   flusher_thread_;

    void readerLoop() {
        while (true) {
            auto res = readRow();
            if (!res) break;
            queue_.push(move(*res));
        }
        queue_.close();
    }

    void workerLoop() {
        vector<TaggedRow> batch;
        auto sizeFn = [](const TaggedRow& r) { return r.second.size(); };

        while (queue_.drain_batch(batch, MAX_BATCH_BYTES, sizeFn)) {
            // Deposit each row into the reorder buffer
            {
                lock_guard<mutex> lk(flush_mtx_);
                for (auto& [seq, data] : batch) {
                    flush_buf_[seq] = move(data);
                }
            }
            flush_cv_.notify_one();
        }

        // Last worker out signals flusher
        if (--active_workers_ == 0) {
            flush_cv_.notify_all();
        }
    }

    void flusherLoop() {
        int next_seq = 0;

        while (true) {
            unique_lock<mutex> lk(flush_mtx_);
            flush_cv_.wait(lk, [&] {
                return flush_buf_.count(next_seq) ||
                       (active_workers_ == 0 && flush_buf_.empty());
            });

            if (active_workers_ == 0 && flush_buf_.empty()) break;

            // Collect consecutive rows up to batch size
            vector<string> batch;
            size_t batch_bytes = 0;

            while (flush_buf_.count(next_seq)) {
                size_t row_sz = flush_buf_[next_seq].size();
                if (!batch.empty() && batch_bytes + row_sz > MAX_BATCH_BYTES)
                    break;
                batch_bytes += row_sz;
                batch.push_back(move(flush_buf_[next_seq]));
                flush_buf_.erase(next_seq);
                next_seq++;
            }
            lk.unlock();

            if (!batch.empty()) writeBatch(batch);
        }
    }

public:
    OrderedCopier() : queue_(MAX_QUEUE_SIZE) {}

    void run() {
        reader_thread_ = thread(&OrderedCopier::readerLoop, this);
        for (int i = 0; i < NUM_WORKERS; i++)
            worker_threads_.emplace_back(&OrderedCopier::workerLoop, this);
        flusher_thread_ = thread(&OrderedCopier::flusherLoop, this);

        reader_thread_.join();
        for (auto& w : worker_threads_) w.join();
        flusher_thread_.join();
    }
};


// ===================== Tester ========================
int main() {
    // UnorderedCopier copier;       // fastest, no ordering
    // OrderedSimpleCopier copier;   // ordered, simple
    // OrderedCopier copier;         // ordered, max throughput

    // copier.run();
    return 0;
}
