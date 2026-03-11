/*
 * Blocking Queue Demo
 *
 * A thread-safe queue where:
 *   - push() adds an item (blocks if queue is full)
 *   - pop()  removes an item (blocks if queue is empty)
 *
 * Classic use: producer-consumer pattern.
 *   Producers push work, consumers pop work.
 *   If queue is empty → consumers sleep.
 *   If queue is full  → producers sleep.
 *
 * Implementation: queue + mutex + 2 condition variables
 *   cvNotEmpty  → wakes consumers when an item is pushed
 *   cvNotFull   → wakes producers when an item is popped
 *
 * Compile: g++ -std=c++11 blocking_queue.cpp -o blocking_queue && ./blocking_queue
 */

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(int maxSize) : _maxSize(maxSize) {}

    void push(T item) {
        unique_lock<mutex> lk(_mtx);
        // Block if queue is full
        _cvNotFull.wait(lk, [this] { return _queue.size() < _maxSize; });

        _queue.push(move(item));
        _cvNotEmpty.notify_one();   // wake a consumer
    }

    T pop() {
        unique_lock<mutex> lk(_mtx);
        // Block if queue is empty
        _cvNotEmpty.wait(lk, [this] { return !_queue.empty(); });

        T item = move(_queue.front());
        _queue.pop();
        _cvNotFull.notify_one();    // wake a producer
        return item;
    }

    int size() {
        unique_lock<mutex> lk(_mtx);
        return _queue.size();
    }

private:
    queue<T> _queue;
    int _maxSize;
    mutex _mtx;
    condition_variable _cvNotEmpty;   // "queue has items" signal
    condition_variable _cvNotFull;    // "queue has space" signal
};

// ─── Demo: 2 producers, 3 consumers, capacity 3 ───

BlockingQueue<int> bq(3);  // max 3 items in queue

void producer(int id) {
    for (int i = 0; i < 4; i++) {
        int item = id * 100 + i;
        cout << "Producer " << id << " pushing " << item << "\n";
        bq.push(item);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 3; i++) {
        int item = bq.pop();       // blocks if empty!
        cout << "  Consumer " << id << " got " << item << "\n";
        this_thread::sleep_for(chrono::milliseconds(300));  // slow consumer
    }
}

int main() {
    // 2 producers × 4 items = 8 items total
    // 3 consumers × 3 items = 9 pops (last one may need a dummy)
    // keeping it simple: 2 producers push 4 each, 2 consumers pop 4 each

    vector<thread> threads;

    // 2 producers, each pushes 4 items
    threads.emplace_back(producer, 0);
    threads.emplace_back(producer, 1);

    // 2 consumers, each pops 4 items (total 8 = matches producers)
    threads.emplace_back([]{
        for (int i = 0; i < 4; i++) {
            int item = bq.pop();
            cout << "  Consumer A got " << item << "\n";
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    });
    threads.emplace_back([]{
        for (int i = 0; i < 4; i++) {
            int item = bq.pop();
            cout << "  Consumer B got " << item << "\n";
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    });

    for (auto& t : threads) t.join();

    cout << "\nAll done! Queue size: " << bq.size() << "\n";
    return 0;
}
