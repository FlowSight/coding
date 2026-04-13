#include<bits/stdc++.h>
#include<semaphore>

using namespace std;

// Two-lock queue with semaphores (C++20)
// - Ring buffer: no heap allocs per push/pop, cache-friendly
// - Separate head_mtx / tail_mtx: push and pop run concurrently
// - Counting semaphores: no lost-wakeup issues (unlike CVs, they maintain state)
template <typename T>
class BoundedThreadSafeQueue {
    public:
    explicit BoundedThreadSafeQueue(int capacity)
        : buf(capacity), cap(capacity),
          sem_slots(capacity),  // empty slots available for push
          sem_items(0) {}       // items available for pop

    void stop(){
        stopped = true;
        // Release enough to wake all blocked pushers and poppers
        sem_slots.release(cap);
        sem_items.release(cap);
    }

    bool push(T item) {
        sem_slots.acquire();            // block until a slot is free (or stop wakes us)
        if(stopped) return false;
        {
            lock_guard<mutex> lg(tail_mtx);  // only contends with other pushers
            buf[tail] = std::move(item);
            tail = (tail + 1) % cap;
        }
        sem_items.release();            // signal: one more item available for pop
        cout<<"Pushed "<<item<<endl;
        return true;
    }

    bool pop() {
        sem_items.acquire();            // block until an item exists (or stop wakes us)
        if(stopped) return false;
        T item;
        {
            lock_guard<mutex> lg(head_mtx);  // only contends with other poppers
            item = std::move(buf[head]);
            head = (head + 1) % cap;
        }
        sem_slots.release();            // signal: one more slot available for push
        cout<<"Popped "<<item<<endl;
        return true;
    }

    private:
    vector<T> buf;
    int cap;
    int head = 0, tail = 0;
    mutex head_mtx, tail_mtx;           // separate locks → push ∥ pop
    counting_semaphore<> sem_slots;     // tracks empty slots
    counting_semaphore<> sem_items;     // tracks available items
    atomic<bool> stopped{false};
};

void testmethod(){
    BoundedThreadSafeQueue<int> btsq(3);
    vector<thread> workers;
    for(auto i=0;i<10;i++){
        if(rand()%2) {
            workers.emplace_back(&BoundedThreadSafeQueue<int>::pop,&btsq);
        }
        else {
            workers.emplace_back(&BoundedThreadSafeQueue<int>::push,&btsq,i);
        }
    }
    this_thread::sleep_for(chrono::milliseconds(10000));
    btsq.stop();
    for(auto &w : workers) {
        if(w.joinable()) w.join();
    }
}

int main(){
    testmethod();
    return 0;
}