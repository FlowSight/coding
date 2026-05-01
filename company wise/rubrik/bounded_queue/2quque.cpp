#include<bits/stdc++.h>
#include<semaphore>

using namespace std;

// Dual-queue sharing one buffer (free-list based, C++20)
// - Shared slot pool: both queues draw from & return to the same free list
// - Per-queue linked list via nxt[] array (no heap allocs)
// - sem_slots: shared capacity pressure across both queues
// - sem_items per queue: independent pop blocking
template <typename T>
class DualQueue {
    // Per-queue state
    struct QState {
        int head = -1, tail = -1;
        mutex mtx;
        counting_semaphore<> sem_items{0};
    };

    public:
    explicit DualQueue(int capacity)
        : buf(capacity), nxt(capacity), cap(capacity),
          sem_slots(capacity) {
        // Build free list: 0 → 1 → 2 → ... → cap-1 → -1
        for (int i = 0; i < capacity - 1; i++) nxt[i] = i + 1;
        nxt[capacity - 1] = -1;
        free_head = 0;
    }

    void stop(){
        stopped = true;
        sem_slots.release(cap);
        q1.sem_items.release(cap);
        q2.sem_items.release(cap);
    }

    bool push_q1(T item) { return push(q1, std::move(item)); }
    bool push_q2(T item) { return push(q2, std::move(item)); }
    bool pop_q1()  { return pop(q1, "q1"); }
    bool pop_q2()  { return pop(q2, "q2"); }

    private:
    bool push(QState& qs, T item) {
        sem_slots.acquire();                // block until any slot is free (shared)
        if (stopped) return false;

        // Grab a slot from the free list
        int slot;
        {
            lock_guard<mutex> lg(free_mtx);
            slot = free_head;
            free_head = nxt[slot];
        }
        buf[slot] = std::move(item);
        nxt[slot] = -1;

        // Link into this queue's tail
        {
            lock_guard<mutex> lg(qs.mtx);
            if (qs.tail == -1)
                qs.head = slot;             // queue was empty
            else
                nxt[qs.tail] = slot;        // append after current tail
            qs.tail = slot;
        }
        qs.sem_items.release();             // signal: one more item in this queue
        cout << "Pushed " << buf[slot] << endl;
        return true;
    }

    bool pop(QState& qs, const char* name) {
        qs.sem_items.acquire();             // block until this queue has an item
        if (stopped) return false;

        T item;
        int slot;
        {
            lock_guard<mutex> lg(qs.mtx);
            slot = qs.head;
            qs.head = nxt[slot];
            if (qs.head == -1) qs.tail = -1; // queue is now empty
        }
        item = std::move(buf[slot]);

        // Return slot to free list
        {
            lock_guard<mutex> lg(free_mtx);
            nxt[slot] = free_head;
            free_head = slot;
        }
        sem_slots.release();                // signal: one more slot available (shared)
        cout << "Popped " << item << " from " << name << endl;
        return true;
    }

    vector<T> buf;                          // shared buffer
    vector<int> nxt;                        // next pointers (free list + queue chains)
    int cap;
    int free_head;
    mutex free_mtx;                         // protects free list
    counting_semaphore<> sem_slots;         // shared: total free slots
    QState q1, q2;                          // independent queue states
    atomic<bool> stopped{false};
};

void testmethod(){
    DualQueue<int> dq(6);
    vector<thread> workers;
    for (auto i = 0; i < 10; i++) {
        int r = rand() % 4;
        if (r == 0)
            workers.emplace_back(&DualQueue<int>::push_q1, &dq, i);
        else if (r == 1)
            workers.emplace_back(&DualQueue<int>::push_q2, &dq, i);
        else if (r == 2)
            workers.emplace_back(&DualQueue<int>::pop_q1, &dq);
        else
            workers.emplace_back(&DualQueue<int>::pop_q2, &dq);
    }
    this_thread::sleep_for(chrono::milliseconds(10000));
    dq.stop();
    for (auto &w : workers) {
        if (w.joinable()) w.join();
    }
}

int main(){
    testmethod();
    return 0;
}