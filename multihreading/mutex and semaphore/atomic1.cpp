#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

atomic<int> totalCount{0}, maxSeen{0};
thread_local int localInt = 0;
//double finalval = 1e6;

void worker(int id) {
    // increment totalCount 1,000,000 times
    // track how many this thread did
    int current = totalCount.load();
    int prevMax = maxSeen.load();


    for(auto i=0;i<1e6;i++) {
        totalCount++;
        localInt++;
        while (current > prevMax) {
            if (maxSeen.compare_exchange_weak(prevMax, current))
                break;
        }
    }
    cout<<"thread id: " <<id<<" contri: "<<localInt<<" global val: "<<totalCount<<endl; 
    
}

int main() {
    localInt = 0;
    vector<thread> threads;
    for (int i = 0; i < 4; i++)
        threads.emplace_back(worker, i);
    for (auto& t : threads) t.join();

    cout << "Total: " << totalCount << "\n";  // must be 4000000
    // print per-thread counts
}