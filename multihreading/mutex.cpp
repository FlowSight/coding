#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex mtx; // Mutex for critical section
int counter = 0; // Shared resource

void increment_counter(int id) {
    for (int i = 0; i < 5; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));
        
        // Lock the mutex before accessing the shared resource
        mtx.lock();
        counter++;
        cout << "Thread " << id << " incremented counter to " << counter << endl;
        // Unlock the mutex after done
        mtx.unlock();
    }
}
int main() {
    thread t1(increment_counter, 1);
    thread t2(increment_counter, 2);
    t1.join();
    t2.join();
    cout << "Final counter value: " << counter << endl;
    return 0;
}
