#include <bits/stdc++.h>
using namespace std;

// ---- Mock APIs ----
optional<pair<int, string>> read() {
    return nullopt; // assume implemented
}

void write(const vector<string>& batch) {
    // thread-safe
}

// ---- Config ----
const int NUM_READERS = 4;
const size_t MAX_QUEUE_SIZE = 1000;
const size_t MAX_BATCH_SIZE = 1 * 1024 * 1024;

// ---- Shared Queue ----
queue<pair<int, string>> q;
mutex q_mtx;
condition_variable cv_not_empty, cv_not_full;

atomic<bool> done_reading{false};
atomic<int> active_readers{NUM_READERS};

// ---- Reader ----
void reader_worker() {
    while (true) {
        auto res = read();
        if (!res.has_value()) break;

        unique_lock<mutex> lock(q_mtx);
        cv_not_full.wait(lock, [] {
            return q.size() < MAX_QUEUE_SIZE;
        });

        q.push(move(res.value()));
        lock.unlock();

        cv_not_empty.notify_one();
    }

    if (--active_readers == 0) {
        done_reading = true;
        cv_not_empty.notify_all();
    }
}

// ---- Writer ----
void writer() {
    map<int, string> buffer; // ordered
    int next_expected = 0;

    while (true) {
        unique_lock<mutex> lock(q_mtx);

        cv_not_empty.wait(lock, [&]() {
            return !q.empty() || done_reading;
        });

        while (!q.empty()) {
            auto [id, row] = move(q.front());
            q.pop();
            buffer[id] = move(row);
        }

        bool should_exit = done_reading && q.empty() && buffer.empty();

        lock.unlock();
        cv_not_full.notify_all();

        if (should_exit) break;

        // Build ordered batch
        vector<string> batch;
        size_t current_size = 0;

        while (buffer.count(next_expected)) {
            string& row = buffer[next_expected];
            size_t row_size = row.size();

            if (!batch.empty() &&
                current_size + row_size > MAX_BATCH_SIZE) {
                break;
            }

            current_size += row_size;
            batch.push_back(move(row));
            buffer.erase(next_expected);
            next_expected++;
        }

        if (!batch.empty()) {
            write(batch);
        }
    }
}

// ---- Driver ----
int main() {
    vector<thread> readers;

    for (int i = 0; i < NUM_READERS; i++) {
        readers.emplace_back(reader_worker);
    }

    thread writer_thread(writer);

    for (auto& t : readers) t.join();
    writer_thread.join();

    return 0;
}