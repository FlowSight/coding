#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void worker_function(int id) {
    cout << "Worker thread " << id << " started" << endl;
    
    // Simulate some work
    for (int i = 0; i < 5; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Worker " << id << " working... step " << (i+1) << endl;
    }
    
    cout << "Worker thread " << id << " finished" << endl;
}

void demo_bad_exit() {
    cout << "\n=== DEMO: Main exits without join/detach (BAD) ===" << endl;
    
    thread worker(worker_function, 1);
    
    // Main thread exits immediately without join() or detach()
    // This will cause std::terminate() to be called!
    cout << "Main thread exiting immediately..." << endl;
}

void demo_with_join() {
    cout << "\n=== DEMO: Main waits with join() (GOOD) ===" << endl;
    
    thread worker(worker_function, 2);
    
    cout << "Main thread waiting for worker to finish..." << endl;
    worker.join(); // Wait for worker to complete
    cout << "Main thread finished after worker completed" << endl;
}

void demo_with_detach() {
    cout << "\n=== DEMO: Main detaches and exits (RISKY) ===" << endl;
    
    thread worker(worker_function, 3);
    
    worker.detach(); // Detach the thread
    cout << "Main thread detached worker and exiting..." << endl;
    
    // Sleep briefly to see some worker output before main exits
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Main thread finished (worker may still be running)" << endl;
}

int main() {
    cout << "Thread Exit Behavior Demonstration" << endl;
    
    // Demo 1: Proper handling with join
    demo_with_join();
    
    // Demo 2: Detaching (worker may be killed when main exits)
    demo_with_detach();
    
    // Demo 3: Bad practice (commented out to avoid crash)
    demo_bad_exit();
    
    cout << "\nProgram completed." << endl;
    return 0;
}