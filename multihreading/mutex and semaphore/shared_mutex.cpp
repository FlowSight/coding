


#include <iostream>
#include <numeric>
#include <chrono>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <mutex>
using namespace std;



volatile int resource = 0;
shared_mutex rwmut;



void readFunc(int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    shared_lock<shared_mutex> sl(rwmut);

    cout << "read: " << resource << endl;

}



void writeFunc(int waitTime) {
    std::this_thread::sleep_for(std::chrono::seconds(waitTime));

    unique_lock<shared_mutex> ul(rwmut);

    resource = rand()%100;
    cout << "write: " << resource << endl;
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    vector<thread> lstThRead;
    vector<thread> lstThWrite;
    int lstArg[NUM_ARGS];

    std::iota(lstArg, lstArg + NUM_ARGS, 0);

    for (int i = 0; i < NUM_THREADS_READ; i++) {
        int arg = lstArg[ rand()%NUM_ARGS ];
        lstThRead.emplace_back(readFunc, arg);
    }

    for (int i = 0; i < NUM_THREADS_WRITE; i++) {
        int arg = lstArg[ rand()%NUM_ARGS ];
        lstThWrite.emplace_back(writeFunc, arg);
    }

    for (auto& th : lstThRead) th.join();
    for (auto& th : lstThWrite) th.join();

    return 0;
}